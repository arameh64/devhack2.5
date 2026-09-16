/* input an integr,
make a function 

*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sender(int signum, int pid)
{
kill(pid, signum);
}

void handler (int signum)
{
    switch (signum)
    {
        case 1:
            printf ("sighup recieved\n");
            break;
        case 2:
            printf ("sigint recieved\n");
            break;
        case 3:
            printf ("sigquit recieved\n");
            break;
        case 4:
            printf ("sigill recieved\n");
            break;
        case 5:
            printf ("sigtrap recieved\n");
            break;
        case 6:
            printf ("sigabrt recieved\n");
            break;
        case 7:
            printf ("sigbus recieved\n");
            break;
        case 8:
            printf ("sigfpe recieved\n");
            break;
        case SIGUSR1:
            printf ("sigusr1 recieved\n");   
            break;                  
    }



}


int main()
{
    int signum = 0;
    printf("enter a signal number ");
    scanf("%d" , &signum);










    if(signum == 9 )
    {
        printf("cant handle that will send sigusr 1   \n");
        signum = SIGUSR1;
    }


    signal(signum, handler);
    sender(signum , 0);

}