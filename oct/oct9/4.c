#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    char filename[256];
    printf("enter file name: ");
    if(scanf("%s", filename)!=1)
        exit(1);

    int fd=open(filename, O_RDONLY);
    if(fd<0)
    {
        perror("open");
        exit(1);
    }

    off_t size=lseek(fd, 0, SEEK_END);
    printf("Ֆայլի չափը՝ %ld բայթ\n", (long)size);

    lseek(fd, 0, SEEK_SET);

    printf("Առաջին տողը՝ ");
    char c;
    while(read(fd, &c, 1)==1 && c!='\n')
        putchar(c);
    putchar('\n');

    close(fd);
    return 0;
}
