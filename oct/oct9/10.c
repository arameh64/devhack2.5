#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int choice;
    char line[256], longest[256];
    while(1)
    {
        printf("1 - add entry\n2 - show all entries\n3 - stats\n4 - clear diary\n0 - exit\n");
        scanf("%d", &choice);
        getchar();

        if(choice==0)
        {
            break;
        }
        else if(choice==1)
        {
            printf("enter text: ");
            fgets(line, sizeof(line), stdin);
            int fd=open("diary.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
            write(fd, line, strlen(line));
            close(fd);
        }
        else if(choice==2 || choice==3)
        {
            FILE *fd=fopen("diary.txt", "r");
            int count=0;
            longest[0]='\0';
            if(fd)
            {
                while(fgets(line, sizeof(line), fd))
                {
                    count++;
                    if(choice==2)
                    {
                        printf("%d. %s", count, line);
                    }
                    if(strlen(line)>strlen(longest))
                    {
                        strcpy(longest, line);
                    }
                }
                fclose(fd);
            }
            if(count==0)
            {
                printf("diary is empty\n");
            }
            else if(choice==3)
            {
                printf("entries: %d\n", count);
                printf("longest entry: %s", longest);
            }
        }
        else if(choice==4)
        {
            char c;
            printf("are you sure? (y/n): ");
            scanf("%c", &c);
            getchar();
            if(c=='y')
            {
                int fd=open("diary.txt", O_WRONLY | O_TRUNC);
                close(fd);
            }
        }
    }
    return 0;
}
