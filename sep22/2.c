#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void execer(void)
{
    char *argvv[] = {"ps", "-ef", NULL};
    execvp("ps", argvv);       
    perror("exec failed");     
    exit(1);
}

int main(void)
{
    execer();
    return 0;                  
}