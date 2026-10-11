#include<stdlib.h>
#include<stdio.h>
#include<time.h>

void printhist(int f, int r, int* arr)
{
    printf("F=%d, R=%d\n", f, r);
    for(int i=0; i<f; i++)
    {
        printf("%d | ", i+1);
        for(int j=0; j<arr[i]; j++)
        {
            printf("*");
        }
        printf(" (%d)\n", arr[i]);
    }
}

int main()
{
    srand(time(NULL));

    int f=0;
    printf("enter number of sides:");
    scanf("%d",&f);

    int r=0;
    printf("enter number of tosses:");
    scanf("%d",&r);

    int* arr = (int *)calloc(f,sizeof(int));
    if(arr==NULL)
    {
        return 1;
    }

    for (int i=0; i<r; i++)
    {
        int x = rand() %f +1;
        arr[x-1]++;
    }

    printhist(f,r,arr);

    free(arr);
    return 0;
}