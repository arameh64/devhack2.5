#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s <file> <word>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    int count = 0;
    char word[64];

    while (fscanf(fp, "%63s", word) == 1) {
        if (strcmp(word, argv[2]) == 0) {
            count++;
        }
    }

    fclose(fp);
    printf("was found %d times\n", count);
    return 0;
}