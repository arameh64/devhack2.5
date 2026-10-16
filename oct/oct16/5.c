#include<stdio.h>
#include<stdlib.h>

int *unique(const int *arr,int n,int *new_n)
{
int *res=malloc(sizeof(int)*n);
int k=0;
for(int i=0;i<n;i++)
{
int seen=0;
for(int j=0;j<k;j++)
{
if(res[j]==arr[i])
{
seen=1;
break;
}
}
if(!seen)
{
res[k++]=arr[i];
}
}
if(k>0)
{
int *t=realloc(res,sizeof(int)*k);
if(t)
{
res=t;
}
}
*new_n=k;
return res;
}

int main(void)
{
int arr[]={4,2,4,7,2,2,9,7};
int n=sizeof(arr)/sizeof(arr[0]);
int m;
int *u=unique(arr,n,&m);
printf("unique (%d): ",m);
for(int i=0;i<m;i++)
{
printf("%d ",u[i]);
}
printf("\n");
free(u);
return 0;
}