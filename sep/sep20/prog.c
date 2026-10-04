#include<stdio.h>
#include<unistd.h>

int main()
{
    while(1)
    {
    sleep(2);
    printf("hello world\n");
    }
    return 0;
}