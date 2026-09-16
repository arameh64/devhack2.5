#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

const int a = 5;

void SigBusHand (int signum )
{

    if (signum == SIGBUS)
    {
        printf("\n recieved sigbus\n");
        exit(0);
    } 
}



void SigsegVHand (int signum )
{

    if (signum == SIGSEGV)
    {
        printf("\n recieved sigsegv \n");
        exit(0);
    } 
}


int main()
{
    signal(SIGBUS, SigBusHand);
    signal(SIGSEGV, SigsegVHand);

    int *p = (int *)&a ;
    *p=44;


    return 0;
}

