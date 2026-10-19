#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char **create_grid(int rows, int cols)
{
    char **grid = calloc(rows, sizeof(char *));
    int i;
    int j;

    if (grid == NULL)
    {
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        grid[i] = calloc(cols, sizeof(char));
        if (grid[i] == NULL)
        {
            for (j = 0; j < i; j++)
            {
                free(grid[j]);
            }
            free(grid);
            return NULL;
        }

        for (j = 0; j < cols; j++)
        {
            grid[i][j] = '.';
        }
    }

    return grid;
}

void free_grid(char **grid, int rows)
{
    int i;

    if (grid == NULL)
    {
        return;
    }

    for (i = 0; i < rows; i++)
    {
        free(grid[i]);
    }
    free(grid);
}

void print_grid(char **grid, int rows, int cols)
{
    int i;
    int j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            putchar(grid[i][j]);
        }
        putchar('\n');
    }
}

int count_neighbors(char **grid, int rows, int cols, int r, int c)
{
    int count = 0;
    int dr;
    int dc;

    for (dr = -1; dr <= 1; dr++)
    {
        for (dc = -1; dc <= 1; dc++)
        {
            int nr = r + dr;
            int nc = c + dc;

            if (dr == 0 && dc == 0)
            {
                continue;
            }

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
            {
                if (grid[nr][nc] == '#')
                {
                    count++;
                }
            }
        }
    }

    return count;
}

void next_generation(char **current, char **next, int rows, int cols)
{
    int i;
    int j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            int n = count_neighbors(current, rows, cols, i, j);

            if (current[i][j] == '#')
            {
                if (n == 2 || n == 3)
                {
                    next[i][j] = '#';
                }
                else
                {
                    next[i][j] = '.';
                }
            }
            else
            {
                if (n == 3)
                {
                    next[i][j] = '#';
                }
                else
                {
                    next[i][j] = '.';
                }
            }
        }
    }
}

int main(void)
{
    int rows;
    int cols;
    int generations;
    int g;
    char **current;
    char **next;
    char **tmp;

    printf("enter rows: ");
    if (scanf("%d", &rows) != 1)
    {
        printf("invalid input\n");
        return 1;
    }

    printf("enter columns: ");
    if (scanf("%d", &cols) != 1)
    {
        printf("invalid input\n");
        return 1;
    }

    printf("enter number of generations: ");
    if (scanf("%d", &generations) != 1)
    {
        printf("invalid input\n");
        return 1;
    }

    if (rows < 3 || cols < 3)
    {
        printf("the grid must be at least 3x3\n");
        return 1;
    }

    if (generations < 0)
    {
        printf("generations must not be negative\n");
        return 1;
    }

    current = create_grid(rows, cols);
    next = create_grid(rows, cols);

    if (current == NULL || next == NULL)
    {
        printf("memory allocation failed\n");
        free_grid(current, rows);
        free_grid(next, rows);
        return 1;
    }

\    current[0][1] = '#';
    current[1][2] = '#';
    current[2][0] = '#';
    current[2][1] = '#';
    current[2][2] = '#';

    printf("\ngeneration 0\n");
    print_grid(current, rows, cols);

    for (g = 1; g <= generations; g++)
    {
        usleep(200000);

        next_generation(current, next, rows, cols);

        printf("\ngeneration %d\n", g);
        print_grid(next, rows, cols);

        tmp = current;
        current = next;
        next = tmp;
    }

    free_grid(current, rows);
    free_grid(next, rows);

    printf("\ndone\n");
    return 0;
}