#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n=0;
    printf("enter how many days: ");
    scanf("%d\n", &n);

    double* arr=(double*)malloc(n*sizeof(double));

    double sum=0;
    for(int i=0; i<n; i++)
    {
        printf("enter temperature of day%d: ",i);
        scanf("%lf\n", &arr[i]);
        sum+=arr[i];
    }

    double avg=sum/n;
    printf("averege temp was:%lf\n", avg);
    for(int i=0; i<n; i++)
    {
        if(arr[i]>avg)
        {
            printf("day%d was hotter", i);
        }
    }

    free(arr);
}