#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define LEN 256

char* find_path(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            continue; 
        }
        else
        {
            return argv[i];
        }
    }
    return NULL; 
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        exit(1);
    }

    char* fpath = find_path(argc, argv);
    char buf[LEN];

    int fd = open(fpath, O_RDONLY);
    if (fd < 0) {
        perror("open failed");
        exit(-1);
    }

    ssize_t n;
    while ((n = read(fd, buf, LEN)) > 0) {
        write(STDOUT_FILENO, buf, n);
    }

    if (n < 0) {
        perror("read went wrong due to whatever reason");
        close(fd);
        exit(-1);
    }

    close(fd);
    return 0;
}