#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

void sigusr1Hand(int signum)
{
    if(signum == SIGUSR1)
    {
        printf("[CHILD] Received SIGUSR1 signal!\n");
        fflush(stdout);
    }
}

void chld()
{
    signal(SIGUSR1, sigusr1Hand);
    while(1)
    {
        pause();
    }
}

pid_t ForkWrap(void)
{
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    return pid;
}

int main()
{
    pid_t pid = ForkWrap();
    if( pid == 0)
    {
        chld();
        return 0;
    }
    if(pid > 0)
    {
        sleep(1);
        kill(pid, SIGUSR1);
        sleep(1);
        kill(pid, SIGTERM);

        int status = 0 ;
        waitpid(pid, &status, 0);

        if(WIFSIGNALED(status))
        {
            printf("[PARENT] Child was killed by signal: %d (%s)\n", WTERMSIG(status), strsignal(WTERMSIG(status)));
        }
        

    }



}