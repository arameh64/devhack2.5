#include<stdio.h>
#include<stdlib.h>


struct student
{
    int grade;
    char name[64];
};

int main()
{
    FILE *fd=fopen("grades.txt", "w");
    if(!fd)
    {
        perror("fopen");
        exit(1);
    }

    struct student std[5];
    for(int i=0; i<5; i++)
    {
        printf("enter student %d name: ", i+1);
        scanf("%s",std[i].name);
        printf("enter student %d grade: ", i+1);
        if(scanf("%d",&std[i].grade)!=1 || std[i].grade<0 || std[i].grade>100)
        {
            fprintf(stderr, "grade not valid\n");
            exit(1);
        }

        fprintf(fd, "%s %d\n", std[i].name, std[i].grade);
    }

    fclose(fd);

    fd=fopen("grades.txt", "r");
    if(!fd)
    {
        perror("fopen");
        exit(1);
    }

    struct student s, best={-1, ""};
    int sum=0, count=0;
    while(fscanf(fd, "%s %d", s.name, &s.grade)==2)
    {
        sum+=s.grade;
        count++;
        if(s.grade>best.grade)
            best=s;
    }
    fclose(fd);

    if(count==0)
        return 1;

    printf("Միջին գնահատական՝ %.2f\n", (double)sum/count);
    printf("Լավագույն ուսանող՝ %s (%d)\n", best.name, best.grade);
    return 0;
}
