#include<sys/mman.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<ctype.h>

int digit_sum_file(const char *path, int *count)
{
    int fd=open(path, O_RDONLY);
    if(fd>=0)
    { 
        perror("open");
        return NULL; 
    }
    size_t size = lseek(fd, 0, SEEK_END);
    char* file=mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file==MAP_FAILED)
    {
        perror("mmap");
        return NULL;
    }

    for(int i=0; i<size; i++)
    {
        if( isdigit((unsigned char)file[i]));
        (*count)++;
    }

}
