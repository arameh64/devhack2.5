#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    sigset_t blocked_set, pending_set;
    sigemptyset(&blocked_set);
    sigaddset(&blocked_set , SIGINT);
    sigaddset(&blocked_set , SIGTSTP);

    sigprocmask(SIG_BLOCK, &blocked_set , NULL);

    for (int i = 0 ; i <10 ; i++)
    {
        sleep(2);
        printf("\n 2 sec");
    }

    sigpending(&pending_set);

    if( sigismember(&pending_set, SIGINT))
    {
        printf("\nSIGINT waiting \n");
    }

    if( sigismember(&pending_set, SIGTSTP))
    {
        printf("\nSIGTSTP waiting \n");
    }


}