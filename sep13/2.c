#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void SigHand(int signum)
{
    if (signum == SIGINT)
    {
        printf("ctrl c sigint");
    }
    if (signum == SIGTSTP)
    {
        printf("ctrl z sigtstp");
    }
}

int main()
{
    signal(SIGINT, SigHand);
    signal(SIGTSTP, SigHand);


    while(1)
    {
        sleep(2);
        printf("\n 2 sec");
    }
}