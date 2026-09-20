#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
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

int main(int argc, char* argv[])
{

if(argc < 2)
{
exit(1);
}

pid_t mypid = getpid();
printf("parent is running pid=%d\n", mypid);

char * path = argv[1];

pid_t pid = ForkWrap();
if(pid == 0)
{           //this scope is the childs code since child gets pid==0
pid_t ppid = getppid();
pid_t mypid = getpid();
printf("childe is running pid=%d ppid=%d\n", mypid, ppid);

execvp(path, &argv[1]);  

perror("failed exec");
exit(1);
}
else if (pid > 0)
{
int status;
wait(&status);

if(WIFEXITED(status))
{
printf("child was exited %d \n", WEXITSTATUS(status));
}

}

printf("parent done\n");
return 0;
}