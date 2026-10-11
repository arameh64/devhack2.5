#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *repeat(const char *word, int n)
{
size_t size = strlen(word);     //og size of word
size *= n;                      //size of work for n times
size+=n;                        //size of all - symbold
size++ ;                        //size of null terminator

char* ret=malloc(sizeof(char)*size);
char min="-";

for(int i=0; i<n; i++)
{
    strcat(ret, word);
    strcat(ret,min);
}

size=strlen(ret);
ret[size]="\0";

return ret;
}

int main()
{
    char word[]={"RepeatMe"};
    char *word2=repeat(word,5);

    printf("%s", word2);

    return 0;
}