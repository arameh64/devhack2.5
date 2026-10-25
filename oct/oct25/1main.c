#include <stdio.h>
#include "log_search.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <word>\n", argv[0]);
        return 1;
    }

    int size = 0;
    char *data = map_log(argv[1], &size);
    if (data == NULL)
        return 1;

    int count = count_word(data, size, argv[2]);
    printf("«%s» բառը հանդիպում է %d անգամ\n", argv[2], count);

    unmap_log(data, size);
    return 0;
}