#include<stdio.h>
#include<stdlib.h>

const char chars[] = "ABC...Zabc...z0123456789";

char *generate_password(int length)
{
    char *pswd = malloc(sizeof(char) * length + 1);
    if (pswd == NULL)
        return NULL;

    size_t n = sizeof(chars) - 1;   

    for (int i = 0; i < length; i++)
        pswd[i] = chars[rand() % n];

    pswd[length] = '\0';
    return pswd;
}

int main()
{
    int n=0;
    scanf("enter password length %d \n", &n);
    char* pswd=generate_password(n);
    printf("%s \n", pswd);

}


