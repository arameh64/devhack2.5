#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<math.h>

int binarymaker(int input)
{
    int out = 0;
    int place = 1;

    while (input != 0) {
        out += (input % 2) * place;
        place *= 10;
        input /= 2;
    }
    return out;
}

void sender(int signums, pid_t pid)
{
    int signum = 0;
    int tmp;

    for (int i=0 ; signums!=0l;i++)
    {
        tmp = signums%10;
        signums /= 10;

        if (tmp == 1 )
        {
             kill(pid, SIGUSR1);
        }
        else if (tmp == 0)
        {
             kill(pid, SIGUSR2);
        }
        else
        {
            printf ("not 1 or 0 something went wrong");
        }
    }
}

int main()
{
    int num = 0;
    pid_t pid = 0;
    int signums = 0;

    printf("enter a number");
    scanf("%d" , &num);

    printf("enter a pid");
    scanf("%d" , &pid);

    signums = binarymaker(num);
    sender(signums, pid);

    return 0 ;
}



