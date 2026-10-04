#include <stdio.h>

int main()
{

    FILE* fd = fopen("table.txt", "w");
    if (fd == NULL) {
        perror("fopen");
        return 1;
    }

    for(int i = 1; i<=10; i++){
        for(int j =1; j<=10; j++){

            fprintf(fd, "%4d", i*j);

        }
    
        fprintf(fd, "\n");

    }

}