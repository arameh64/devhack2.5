#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void sender(char* path, int wfd)
{
    FILE* fp = fopen(path, "r");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }

    char line[256];
    while (fgets(line, 256, fp) != NULL)
    {
        write(wfd, line, strlen(line));
    }

    fclose(fp);
}

void reciever(int rfd)
{
    char buf[256];
    int n;

    while ((n = read(rfd, buf, 256)) > 0)
    {
        // counting goes here later
        write(1, buf, n);
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("No path entered\n");
        return 1;
    }

    int fds[2];
    pipe(fds);

    pid_t pid = fork();
    if (pid == 0)
    {
        // child territory
        close(fds[1]);
        reciever(fds[0]);
        close(fds[0]);
    }
    else if (pid > 0)
    {
        // parent territory
        close(fds[0]);
        sender(argv[1], fds[1]);
        close(fds[1]);
        wait(NULL);
    }
    else
    {
        perror("fork went wrong");
    }

    return 0;
}