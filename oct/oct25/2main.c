#include"2func.h"

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        perror("incomplete arguments");
    }
    int count;
    int sum = digit_sum_file(argv[1], &count);
    if (sum < 0)
        return 1;
 
    printf("Թվանշանների քանակը՝ %d\n", count);
    printf("Թվանշանների գումարը՝ %d\n", sum);
    return 0;
}


