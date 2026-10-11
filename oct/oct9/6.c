#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int in=open("dirty.txt", O_RDONLY);
    if(in<0)
    {
        perror("dirty.txt");
        exit(1);
    }

    int out=open("clean.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if(out<0)
    {
        perror("clean.txt");
        close(in);
        exit(1);
    }

    char buf[256], outbuf[256];
    char last='\n'; // last written char survives across buffers; '\n' drops leading empty lines
    ssize_t n;
    while((n=read(in, buf, sizeof buf))>0)
    {
        int k=0;
        for(ssize_t i=0; i<n; i++)
        {
            char c=buf[i];
            if(c==' ' && last==' ')
                continue;
            if(c=='\n' && last=='\n')
                continue;
            outbuf[k++]=c;
            last=c;
        }
        if(write(out, outbuf, k)!=k)
        {
            perror("write");
            exit(1);
        }
    }

    off_t in_size=lseek(in, 0, SEEK_END);
    off_t out_size=lseek(out, 0, SEEK_END);
    printf("dirty.txt՝ %ld բայթ\n", (long)in_size);
    printf("clean.txt՝ %ld բայթ\n", (long)out_size);
    printf("Փոքրացավ՝ %ld բայթով\n", (long)(in_size-out_size));

    close(in);
    close(out);
    return 0;
}
