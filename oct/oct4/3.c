#include <stdio.h>
#include <limits.h>

struct stats
{
    int num;
    int count;
    int sum;
    int largest;
    int smallest;
};

int main()
{
    FILE *fd = fopen("numbers.txt", "r");
    if (fd == NULL)
    {
        perror("fopen");
        return 1;
    }

    struct stats s = {0, 0, 0, INT_MIN, INT_MAX};

    while (fscanf(fd, "%d", &s.num) == 1)
    {
        s.count++;
        s.sum += s.num;
        if (s.largest < s.num)
        {
            s.largest = s.num;
        }
        if (s.smallest > s.num)
        {
            s.smallest = s.num;
        }
    }

    printf("count=%d\n", s.count);
    printf("sum=%d\n", s.sum);
    printf("largest=%d\n", s.largest);
    printf("smallest=%d\n", s.smallest);


    fclose(fd);
    return 0;
}