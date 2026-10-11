#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    FILE *in=fopen("text.txt", "r");
    if(!in)
    {
        perror("text.txt");
        exit(1);
    }

    FILE *out=fopen("censored.txt", "w");
    if(!out)
    {
        perror("censored.txt");
        fclose(in);
        exit(1);
    }

    int c, count=0;
    while((c=fgetc(in))!=EOF)
    {
        if(c && strchr("aeiouAEIOU", c))
        {
            c='*';
            count++;
        }
        fputc(c, out);
    }

    fclose(in);
    fclose(out);

    printf("Փոխարինվեց %d ձայնավոր\n", count);
    return 0;
}
