#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>


pid_t ForkWrap()
{
    pid_t pid = fork();
    if(pid<0)
    {
        perror("fork did not happen\n");
        exit(1);
    }
    else
    {
        return pid;
    }
}

int main()
{
    pid_t mypid = getpid();
    printf("parent is running pid=%d\n", mypid);

    pid_t pid = ForkWrap();
    if(pid == 0)
    {           //this scope is the childs code since child gets pid==0
        pid_t ppid = getppid();
        pid_t mypid = getpid();
        printf("childe is running pid=%d ppid=%d\n", mypid, ppid);

        sleep(2);
        printf("child done\n");
        exit(0);
    }
    else if (pid > 0)
    {
        int status;
        wait(&status);

        if(WIFEXITED(status))
        {
            printf("child was exited %d \n", status);
        }

        
    }

    printf("parent done\n");
    return 0;
}

