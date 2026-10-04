#include <stdio.h>

int main(void)
{
    char name[64] = {0};
    char city[64] = {0};
    int age = 0;

    scanf("%s", name);
    scanf("%s", city);
    scanf("%d", &age);

    FILE *fd = fopen("about_me.txt", "w");
    if (fd == NULL) {
        perror("fopen");
        return 1;
    }

    fprintf(fd, "name=%s\n", name );
    fprintf(fd, "age=%d\n", age);
    fprintf(fd, "city=%s\n", city );
    fclose(fd);



    fd = fopen("about_me.txt", "r");
    if (fd == NULL) {
        perror("fopen");
        return 1;
    }

    char str[128] = {0};
    while (fgets(str, sizeof(str), fd) != NULL) {
        printf("%s", str);
    }

    fclose(fd);
    return 0;
}