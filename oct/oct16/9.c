
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book
{
    char *title;
    int year;
};

void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int main(void)
{
    struct Book *books = NULL;
    int count = 0;
    int choice;
    char buffer[1024];

    while (1)
    {
        printf("\n1 - add book\n");
        printf("2 - delete book by number\n");
        printf("3 - show all books\n");
        printf("4 - find oldest book\n");
        printf("0 - exit\n");
        printf("choice: ");

        if (scanf("%d", &choice) != 1)
        {
            if (feof(stdin))
            {
                break;
            }
            clear_input();
            printf("invalid input\n");
            continue;
        }
        clear_input();

        if (choice == 1)
        {
            int year;
            struct Book *tmp;

            printf("enter title: ");
            if (fgets(buffer, sizeof buffer, stdin) == NULL)
            {
                break;
            }
            buffer[strcspn(buffer, "\n")] = '\0';

            printf("enter year: ");
            if (scanf("%d", &year) != 1)
            {
                clear_input();
                printf("invalid year\n");
                continue;
            }
            clear_input();

            tmp = realloc(books, (count + 1) * sizeof(struct Book));
            if (tmp == NULL)
            {
                printf("memory allocation failed\n");
                continue;
            }
            books = tmp;

            books[count].title = malloc(strlen(buffer) + 1);
            if (books[count].title == NULL)
            {
                printf("memory allocation failed\n");
                continue;
            }
            strcpy(books[count].title, buffer);
            books[count].year = year;
            count++;

            printf("book added\n");
        }
        else if (choice == 2)
        {
            int number;
            int i;

            if (count == 0)
            {
                printf("no books\n");
                continue;
            }

            printf("enter book number (1-%d): ", count);
            if (scanf("%d", &number) != 1)
            {
                clear_input();
                printf("invalid input\n");
                continue;
            }
            clear_input();

            if (number < 1 || number > count)
            {
                printf("no book with that number\n");
                continue;
            }

            free(books[number - 1].title);

            for (i = number - 1; i < count - 1; i++)
            {
                books[i] = books[i + 1];
            }
            count--;

            if (count == 0)
            {
                free(books);
                books = NULL;
            }
            else
            {
                struct Book *tmp = realloc(books, count * sizeof(struct Book));
                if (tmp != NULL)
                {
                    books = tmp;
                }
            }

            printf("book deleted\n");
        }
        else if (choice == 3)
        {
            int i;

            if (count == 0)
            {
                printf("no books\n");
            }
            else
            {
                for (i = 0; i < count; i++)
                {
                    printf("%d. %s (%d)\n", i + 1, books[i].title, books[i].year);
                }
            }
        }
        else if (choice == 4)
        {
            int i;
            int oldest = 0;

            if (count == 0)
            {
                printf("no books\n");
            }
            else
            {
                for (i = 1; i < count; i++)
                {
                    if (books[i].year < books[oldest].year)
                    {
                        oldest = i;
                    }
                }
                printf("oldest book: %s (%d)\n", books[oldest].title, books[oldest].year);
            }
        }
        else if (choice == 0)
        {
            break;
        }
        else
        {
            printf("invalid choice\n");
        }
    }

    for (int i = 0; i < count; i++)
    {
        free(books[i].title);
    }
    free(books);

    printf("goodbye\n");
    return 0;
}