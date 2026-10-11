#include<stdio.h>
#include<string.h>

#define UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWER "abcdefghijklmnopqrstuvwxyz"
#define DIGIT "0123456789"

int check(FILE *in, FILE *strong, FILE *weak, int *s, int *w)
{
    char line[256], reasons[256] = "";
    if (!fgets(line, sizeof line, in)) {
        return 0;
    }
    line[strcspn(line, "\n")] = '\0';
    if (strlen(line) == 0) {
        return 1;
    }

    if (strlen(line) < 8) {
        strcat(reasons, ", too short");
    }
    if (!strpbrk(line, UPPER)) {
        strcat(reasons, ", no uppercase letter");
    }
    if (!strpbrk(line, LOWER)) {
        strcat(reasons, ", no lowercase letter");
    }
    if (!strpbrk(line, DIGIT)) {
        strcat(reasons, ", no digit");
    }
    if (strspn(line, UPPER LOWER DIGIT) == strlen(line)) {
        strcat(reasons, ", no special character");
    }

    if (strlen(reasons) == 0) {
        fprintf(strong, "%s\n", line);
        (*s)++;
    } else {
        fprintf(weak, "%s - %s\n", line, reasons + 2);
        (*w)++;
    }
    return 1;
}

int main()
{
    FILE *in = fopen("passwords.txt", "r");
    if (!in) {
        perror("passwords.txt");
        return 1;
    }
    FILE *strong = fopen("strong.txt", "w");
    FILE *weak = fopen("weak.txt", "w");
    if (!strong || !weak) {
        perror("output");
        return 1;
    }

    int s = 0, w = 0;
    while (check(in, strong, weak, &s, &w)) {
    }

    printf("strong: %d\nweak: %d\n", s, w);
    fclose(in);
    fclose(strong);
    fclose(weak);
    return 0;
}


//used ai to clean up the code but the functionality isn not changed