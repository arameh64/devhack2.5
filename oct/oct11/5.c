#include<stdio.h>
#include<stdlib.h>

int main()
{
    int size=1;
    int exit=1;

    int* arr = malloc(size*sizeof(int));

    int rn=0;

    for(int i=0; exit; i++)
    {
        printf("enter price of %d-th thing: ", i+1);
        scanf("%d", &rn);
        if(rn==0)
        {
            printf("thank you!\n");
            exit=0;
        }
        else 
        {
            size+=1;
            arr = realloc(arr, size*sizeof(int));
            arr[i]=rn;
        }
    }

    for(int i=0; i<size; i++)
    {
        printf("%d, ", arr[i]);
    }


    free(arr);
    return 0;
}