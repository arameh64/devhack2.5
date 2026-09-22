#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

pid_t ForkWrap()
{
pid_t pid = fork();
if(pid<0)
{
perror("fork did not happen");
exit(1);
}
else
{
return pid;
}
}

void child()
{
printf("child: my pid is %d, my parent pid is %d\n", getpid(), getppid());
fflush(stdout);

volatile int *ptr = NULL;
*ptr = 42;

printf("this line should never print\n");
exit(0);
}

void parent(pid_t childpid)
{
int status;

printf("parent: my pid is %d, my child pid is %d\n", getpid(), childpid);

waitpid(childpid, &status, 0);

if(WIFEXITED(status))
{
printf("child exited normally with status %d\n", WEXITSTATUS(status));
}
else if(WIFSIGNALED(status))
{
int sig = WTERMSIG(status);
printf("child was killed by signal %d (%s)\n", sig, strsignal(sig));

if(sig == SIGSEGV)
{
printf("caught it: child had a segmentation fault\n");
}

if(WCOREDUMP(status))
{
printf("core dumped\n");
}
}
}

int main()
{
fflush(stdout);
pid_t pid = ForkWrap();

if(pid==0)
{
child();
}
else
{
parent(pid);
}

return 0;
}