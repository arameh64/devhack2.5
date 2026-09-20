#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX 10

volatile sig_atomic_t hit_count = 0;
volatile sig_atomic_t keep_running = 1;

pid_t peer_id = 0;

void Sigusr1(int signum)
{
if (signum == SIGUSR1)
{
    hit_count++ ;
    printf("[Ping] Parent [%d / %d] \n", hit_count, MAX);
}
}
void Sigusr2(int signum)
{
if (signum == SIGUSR2)
{
    hit_count++ ;
    printf("[Ping] Child [%d / %d] \n", hit_count, MAX);

}
}
void Sigint(int signum)
{
    if(signum == SIGINT)
    {
        keep_running=0;
    }
}
void Sigchld(int signum)
{
    if(signum == SIGCHLD)
    {
        keep_running=0;
    }
}
pid_t ForkWrap()
{
pid_t pid = fork();
if(pid<0)
{
perror("fork did not happen");
exit(1);
}
else
{
return pid;
}
}

int main()
{
    signal(SIGCHLD, Sigchld);

    pid_t ch_pid = ForkWrap();
    if(ch_pid == 0)
    {
        signal(SIGINT, Sigint);
        
        while(keep_running)
        {
            pause();

            

            if(hit_count>MAX)break;
        }
    }











}






