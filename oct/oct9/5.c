#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    char in_name[256], out_name[256], key;
    printf("enter input file: ");
    if(scanf("%255s", in_name)!=1)
        exit(1);
    printf("enter output file: ");
    if(scanf("%255s", out_name)!=1)
        exit(1);
    printf("enter key: ");
    if(scanf(" %c", &key)!=1)
        exit(1);

    int in=open(in_name, O_RDONLY);
    if(in<0)
    {
        perror(in_name);
        exit(1);
    }

    int out=open(out_name, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(out<0)
    {
        perror(out_name);
        close(in);
        exit(1);
    }

    char buf[64];
    ssize_t n;
    while((n=read(in, buf, sizeof buf))>0)
    {
        for(ssize_t i=0; i<n; i++)
            buf[i]^=key;
        if(write(out, buf, n)!=n)
        {
            perror("write");
            exit(1);
        }
    }

    close(in);
    close(out);
    return 0;
}

/*
 Հարց՝ ինչու՞ է նույն ծրագիրը և՛ գաղտնագրում, և՛ վերծանում։
 Պատասխան՝ XOR-ը ինքն իր հակադարձն է՝ (x ^ k) ^ k == x ^ (k ^ k) == x ^ 0 == x։
 Գաղտնագրելիս յուրաքանչյուր բայթ դառնում է x ^ k, իսկ նույն բանալիով
 կրկին XOR անելիս k-ն չեղարկվում է, և ստացվում է սկզբնական x-ը։
*/
