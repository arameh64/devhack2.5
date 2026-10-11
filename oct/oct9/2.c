#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE *fd=fopen("nums.txt", "w");
    if(!fd)
    {
        perror("fopen");
        exit(1);
    }

    for(int i=1; i<=100; i++)
        fprintf(fd, "%d\n", i);

    fclose(fd);

    fd=fopen("nums.txt", "r");
    if(!fd)
    {
        perror("fopen");
        exit(1);
    }

    int n, count=0;
    while(fscanf(fd, "%d", &n)==1)
    {
        if(n%7==0)
        {
            printf("%d ", n);
            count++;
        }
    }
    fclose(fd);

    printf("\nՔանակ՝ %d\n", count);
    return 0;
}
