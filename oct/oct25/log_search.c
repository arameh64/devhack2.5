#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<string.h>

char *map_log(const char *path, int *size)
{
    int fd=open(path, O_RDONLY);
    if(fd<0)
    {
        perror("open");
        return NULL;
    }

    size_t len=lseek(fd, 0, SEEK_END);
    char* file=mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if(file==MAP_FAILED)
    {
        perror("mmap");
        return NULL;
    }

    return file;
}

void unmap_log(char *data, int size)
{
    int ret=munmap(data, size);
    return ret;
}

int count_word(const char *data, int size, const char *word)
{
    int len = (int)strlen(word);
    int count = 0;

    if (data == NULL || len == 0 || len > size)
        return 0;

    for (int i = 0; i <= size - len; i++) {
        if (strncmp(data + i, word, len) == 0)
            count++;
    }
    return count;
}


