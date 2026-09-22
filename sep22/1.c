#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

//use -lm while compiling with gcc

pid_t ForkWrap(void)
{
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    return pid;
}

void ch1(double num)
{
    if (num <= 0) {
        printf("log2: number must be > 0\n");
        exit(1);
    }
    printf("log2(%g) = %f\n", num, log2(num));
    printf("log2 child pid is %d\n", getpid());
}

void ch2(double num)
{
    int n = (int)num;
    if (n < 0 || n > 20) {
        printf("factorial: n must be 0..20 (overflow )\n");
        exit(1);
    }
    unsigned long long total = 1;
    for (int i = 2; i <= n; i++)
        total *= i;
    printf("%d! = %llu\n", n, total);
    printf("factorial child pid is %d\n", getpid());
}

void ch3(double num)
{
    printf("%g^3 = %f\n", num, num * num * num);
    printf("cube child pid is %d\n", getpid());
}

int main(void)
{
    pid_t pids[3];
    double num;

    printf("enter a number: ");
    if (scanf("%lf", &num) != 1) {
        fprintf(stderr, "invalid input\n");
        return 1;
    }
    fflush(stdout);

    for (int i = 0; i < 3; i++) {
        pids[i] = ForkWrap();
        if (pids[i] == 0) {          
            switch (i) {
            case 0: ch1(num); break;
            case 1: ch2(num); break;
            case 2: ch3(num); break;
            }
            exit(0);                 
        }
    }

    pid_t first = wait(NULL);
    printf("parent: first child to finish was %d\n", first);

    for (int i = 0; i < 3; i++)
        if (pids[i] != first)
            kill(pids[i], SIGKILL);

    while (wait(NULL) > 0)            
        ;

    return 0;
}