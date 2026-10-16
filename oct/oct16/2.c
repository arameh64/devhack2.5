#include <stdio.h>
#include <stdlib.h>

void split_sign(const int *arr, int n, int **pos, int *pos_n, int **neg, int *neg_n)
{
    *pos_n = 0;
    *neg_n = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > 0)
            (*pos_n)++;
        else if (arr[i] < 0)
            (*neg_n)++;
    }

    *pos = malloc(*pos_n * sizeof(int));
    *neg = malloc(*neg_n * sizeof(int));

    int p = 0, q = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > 0)
            (*pos)[p++] = arr[i];
        else if (arr[i] < 0)
            (*neg)[q++] = arr[i];
    }
}

int main(void)
{
    int arr[] = {4, -2, 0, 7, -9, 3, 0, -1};
    int n = 8;

    int *pos, *neg;
    int pos_n, neg_n;

    split_sign(arr, n, &pos, &pos_n, &neg, &neg_n);

    printf("pos (%d)", pos_n);
    for (int i = 0; i < pos_n; i++)
        printf(" %d", pos[i]);
    printf("\n");

    printf("neg (%d)՝", neg_n);
    for (int i = 0; i < neg_n; i++)
        printf(" %d", neg[i]);
    printf("\n");

    free(pos);
    free(neg);
    return 0;
}
