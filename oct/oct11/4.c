#include<stdlib.h>
#include<stdio.h>
#define N 6

int *mirror(const int *arr, int n)
{
    int *ret = malloc(sizeof(int) * 2 * n);
    if (ret == NULL)
        return NULL;

    for (int i = 0; i < n; i++) 
    {
        ret[i] = arr[i];               
        ret[2 * n - 1 - i] = arr[i];   
    }
    return ret;
}

int main()
{
    int arr[N] = {1,2,3,4,5,6};
    int* arr2;

    arr2=mirror(arr, N);


    for(int i=0; i<2*N; i++)
    {
        printf("%d\n", arr2[i]);
    }
}