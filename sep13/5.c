#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sender(int signum, int pid)
{
    return kill(pid, signum);
}

void handler(int signum)
{
    switch (signum)
    {
    case SIGHUP:  printf("sighup recieved\n");  break;
    case SIGINT:  printf("sigint recieved\n");  break;
    case SIGQUIT: printf("sigquit recieved\n"); break;
    case SIGILL:  printf("sigill recieved\n");  break;
    case SIGTRAP: printf("sigtrap recieved\n"); break;
    case SIGABRT: printf("sigabrt recieved\n"); break;
    case SIGBUS:  printf("sigbus recieved\n");  break;
    case SIGFPE:  printf("sigfpe recieved\n");  break;
    case SIGUSR1: printf("sigusr1 recieved\n"); break;
    }
}

int main(void)
{
    int n = 0;
    int div = 1;
    int tmp;
    int digit;

    printf("enter a number ");
    if (scanf("%d", &n) != 1)
        return 1;

    if (n < 0)
        n = -n;

    if (n == 0)
    {
        printf("this is 0\n");
        return 0;
    }

    tmp = n;
    while (tmp >= 10)
    {
        tmp /= 10;
        div *= 10;
    }

    while (div > 0)
    {
        digit = (n / div) % 10;

        if (digit == 0)
        {
            printf("this is 0\n");
        }
        else
        {
            if (digit == 9)
            {
                printf("cant handle that will send sigusr1\n");
                digit = SIGUSR1;
            }
            signal(digit, handler);
            sender(digit, getpid());
        }

        div /= 10;
    }

    return 0;
}