#include<stdio.h>
#include<stdlib.h>

struct Player
{
    char name[20];
    int level;
    int score;
    int lives;
};

void print_player(struct Player *p)
{
    printf("%s: level: %d, score: %d, lives: %d\n", p->name, p->level, p->score, p->lives);
}

int main()
{
    struct Player p;
    FILE *fd=fopen("save.dat", "rb");
    if(fd && fread(&p, sizeof(p), 1, fd)==1)
    {
        printf("welcome back, %s. level: %d, score: %d, lives: %d\n", p.name, p.level, p.score, p.lives);
    }
    else
    {
        printf("enter name: ");
        if(scanf("%s", p.name)!=1)
        {
            exit(1);
        }
        p.level=1;
        p.score=0;
        p.lives=3;
    }
    if(fd)
    {
        fclose(fd);
    }

    int n;
    while(1)
    {
        printf("enter number: ");
        if(scanf("%d", &n)!=1)
        {
            fprintf(stderr, "invalid input\n");
            exit(1);
        }

        if(n==0)
        {
            fd=fopen("save.dat", "wb");
            if(!fd)
            {
                perror("fopen");
                exit(1);
            }
            fwrite(&p, sizeof(p), 1, fd);
            fclose(fd);
            break;
        }
        else if(n==-1)
        {
            p.lives--;
        }
        else if(n>0)
        {
            p.score+=n;
        }
        else
        {
            continue;
        }

        p.level=p.score/100+1;
        print_player(&p);

        if(p.lives<=0)
        {
            printf("game over\n");
            remove("save.dat");
            break;
        }
    }
    return 0;
}
