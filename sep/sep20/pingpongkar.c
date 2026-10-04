#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>


#define MAX_COUNT 10


volatile sig_atomic_t hit_count = 0;
volatile sig_atomic_t keep_running = 1;

pid_t peer_id;


void sigint_handler(int signum){
    keep_running = 0;
}
void sigchild_handler(int signum){
    keep_running = 0;
}

void sigusr1_handler(int signum){
    hit_count++;
    printf("[Ping] Parent [ %d / %d ] \n", hit_count, MAX_COUNT);
}

void sigusr2_handler(int signum){
     hit_count++;
    printf("[Pong] Child [ %d / %d ] \n", hit_count, MAX_COUNT);
}

pid_t child_fork(){

    pid_t pid = fork();
    if(pid < 0){
        perror("Failed fork()");
        exit(1);
    }

    return pid;
}

int main(){

    signal(SIGCHLD, sigchild_handler);

    pid_t child_id = child_fork();

    if(child_id == 0){
        signal(SIGINT, sigint_handler);

        signal(SIGUSR1, sigusr1_handler);

        peer_id = getppid();

        while(keep_running && hit_count < MAX_COUNT) {
            pause();

            sleep(1);

            kill(getppid(), SIGUSR2);

        }

        exit(0);


    }else {
        signal(SIGINT, sigint_handler);
        signal(SIGUSR2, sigusr2_handler);

        sleep(2);
        peer_id = child_id;
        kill(peer_id, SIGUSR1);

        while(keep_running && hit_count < MAX_COUNT) {
            pause();

            sleep(1);

            kill(peer_id, SIGUSR1);
        }

        int status;
        wait(&status);

        if(WIFEXITED(status)){
            printf("The child finished the work with status code: %d \n", status);
        }else if(WIFSIGNALED(status)){
            int signum = status;
            printf("The child finished tthe work witht signal: %d \n", signum);
        }

        printf("Parent ended the work \n");
    }

    return 0;
}