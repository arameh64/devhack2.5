#include <stdio.h>
#include <stdlib.h>

int *range(int start, int stop, int step, int *size)
{
    *size = 0;
    if (step == 0)
        return NULL;

    int count = 0;
    for (int i = start; step > 0 ? i < stop : i > stop; i += step)
        count++;

    if (count == 0)
        return NULL;

    int *res = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++)
        res[i] = start + i * step;

    *size = count;
    return res;
}

void show(int start, int stop, int step)
{
    int size;
    int *r = range(start, stop, step, &size);

    printf("range(%d, %d, %d) ->", start, stop, step);
    for (int i = 0; i < size; i++)
        printf(" %d", r[i]);
    printf("\n");

    free(r);
}

int main(void)
{
    show(0, 10, 2);
    show(10, 0, -3);
    show(5, 1, 1);
    return 0;
}
