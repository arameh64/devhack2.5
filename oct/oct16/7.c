#include<stdio.h>
#include<stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *big_add(const char *a, const char *b)
{
    int la = strlen(a);
    int lb = strlen(b);
    int max = (la > lb) ? la : lb;

    char *res = malloc(max + 2);
    if (!res)
    {
        return NULL;
    }

    res[max + 1] = '\0';

    int i = la - 1;
    int j = lb - 1;
    int carry = 0;

    for (int k = max; k >= 0; k--)
    {
        int sum = carry;
        if (i >= 0)
        {
            sum += a[i--] - '0';
        }
        if (j >= 0)
        {
            sum += b[j--] - '0';
        }
        res[k] = sum % 10 + '0';
        carry = sum / 10;
    }

    if (res[0] == '0' && max + 1 > 1)
    {
        memmove(res, res + 1, max + 1);
    }

    return res;
}

int main(void)
{
    const char *tests[][2] =
    {
        {"123", "456"},
        {"999", "1"},
        {"0", "0"},
        {"99999999999999999999", "1"},
        {"12345678901234567890", "98765432109876543210"},
    };
    int n = sizeof(tests) / sizeof(tests[0]);

    for (int t = 0; t < n; t++)
    {
        char *s = big_add(tests[t][0], tests[t][1]);
        if (!s)
        {
            printf("memory error\n");
            return 1;
        }
        printf("%s + %s = %s\n", tests[t][0], tests[t][1], s);
        free(s);
    }

    return 0;
}