#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n=0;
    printf("enter the number of elements");
    scanf("%d",&n);

    int* calarr=calloc(n,sizeof(int));
    int* malarr=malloc(n*sizeof(int));

    for(int i=0; i<n; i++)
    {
        printf("calloc is %d\n", calarr[i]);
        printf("malloc is%d\n",malarr[i]);
    }

    
    free(malarr);
    free(calarr);
}