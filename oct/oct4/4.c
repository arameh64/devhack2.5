#include <stdio.h>
#include <ctype.h>

struct stats
{
    int capitals;
    int smalls;
    int nums;
    int spaces;
    int lines;
    int size;
};

int main(void)
{
    FILE *fd = fopen("text.txt", "r");
    if (fd == NULL)
    {
        perror("fopen");
        return 1;
    }

    int c;
    struct stats s = {0};

    while ((c = fgetc(fd)) != EOF)
    {
        if (islower(c))
            s.smalls++;
        else if (isupper(c))
            s.capitals++;
        else if (isdigit(c))
            s.nums++;
        else if (c == ' ')
            s.spaces++;

        if (c == '\n')
            s.lines++;

        s.size++;
    }

    fclose(fd);

    printf("capitals: %d\nsmalls: %d\nnums: %d\nspaces: %d\nlines: %d\nsize: %d\n",
           s.capitals, s.smalls, s.nums, s.spaces, s.lines, s.size);
    return 0;
}