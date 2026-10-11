#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

int sum_file(const char *name)
{
    FILE *fd=fopen(name, "r");
    if(!fd)
    {
        perror("fopen");
        exit(1);
    }

    int n, sum=0;
    while(fscanf(fd, "%d", &n)==1)
    {
        sum+=n;
    }
    fclose(fd);
    return sum;
}

int main()
{
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
        exit(1);
    }
    if(pid==0)
    {
        FILE *fd=fopen("even.txt", "w");
        if(!fd)
        {
            perror("fopen");
            exit(1);
        }
        for(int i=2; i<=20; i+=2)
        {
            fprintf(fd, "%d\n", i);
        }
        fclose(fd);
        exit(0);
    }

    pid=fork();
    if(pid<0)
    {
        perror("fork");
        exit(1);
    }
    if(pid==0)
    {
        int fd=open("odd.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd<0)
        {
            perror("open");
            exit(1);
        }
        char buf[16];
        for(int i=1; i<=20; i+=2)
        {
            int len=snprintf(buf, sizeof(buf), "%d\n", i);
            write(fd, buf, len);
        }
        close(fd);
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    int even=sum_file("even.txt");
    int odd=sum_file("odd.txt");
    printf("even sum: %d\n", even);
    printf("odd sum: %d\n", odd);
    printf("total: %d\n", even+odd);
    return 0;
}
