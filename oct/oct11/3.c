#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char *my_strdup(const char *s) 
{
    size_t len=strlen(s);
    char *str=malloc(sizeof(char)*(len+1));
    if(str==NULL)
        perror("malloc");
    strcpy(str, s);
    return str;
}

int main()
{
    char str[]={"hello"};
    char *str2=my_strdup(str);

    printf("og:%s \n", str);
    printf("fake:%s \n", str2);

}