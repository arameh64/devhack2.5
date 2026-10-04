#include<stdio.h>

//  ./a.out input.txt output.txt key

int main(int argc, char **argv)
{

    FILE *fdin = fopen(argv[1], "r" );
    FILE *fdout = fopen(argv[2], "r" );
    if( fdin == NULL | fdout==NULL)
    {
        perror("fopen ");
    }

    int key= argv[3];
    int c =0; 
    char s=0;

    s=fgetc(fdin);

    while(s!= NULL)
    {
        s+=key;
        fputc(s, fdout);
        s=fgetc(fdin);

    }


    fclose(fdout);
}