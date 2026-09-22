#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TIMEOUT 3

static volatile pid_t child_pid = 0;
static volatile sig_atomic_t timed_out = 0;

static void alarm_handler(int signo)
{
    (void)signo;
    if (child_pid > 0) {
        kill(child_pid, SIGKILL);            
        timed_out = 1;
        const char msg[] = "[WATCHDOG] Child timed out and killed!\n";
        write(STDOUT_FILENO, msg, sizeof msg - 1);  
    }
}

int main(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_handler = alarm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;                          
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {                            
        sleep(5);                              
        _exit(EXIT_SUCCESS);
    }

    child_pid = pid;                         
    alarm(TIMEOUT);

    int status;
    pid_t r;
    while ((r = waitpid(pid, &status, 0)) == -1 && errno == EINTR)
        ;                                     
    if (r == -1) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    alarm(0);                                 

    if (!timed_out)
        printf("[WATCHDOG] Child finished successfully.\n");

    return EXIT_SUCCESS;
}