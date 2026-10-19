#include<stdio.h>
#include<stdlib.h>

char *load_file(const char *filename, int *size)
{
    FILE *fd=fopen(filename, "rb");
    if(!fd)
    return NULL;

    int flen=16;
    int alen=0;
    char* buf=malloc(flen*sizeof(char));
    if(!buf)
    {
        free(buf);
        return NULL;
    }

    size_t n;

    while(( n=fread(buf+alen, 1, flen-alen, fd))>0)
    {
        alen+=n;
        if(alen==flen)
        {
            char*tmp= realloc(buf, flen*2);
            if(!tmp)
            {
                free(buf);
                return NULL;
            }
            buf=tmp;
            flen*=2;
        }
    }


    buf[alen]='\0';
    *size=alen;


}

int main(int argc, char** argv)
{
    const char *name = (argc > 1) ? argv[1] : "input.txt";
    int size;
    char *text = load_file(name, &size);
    if (!text) { perror(name); return 1; }

    int lines = 0;      
    int line_no = 1;    
    int cur = 0;        
    int max_len = -1, max_line = 0;

    for (int i = 0; i < size; i++) 
    {
        if (text[i] == '\n') 
        {
            if (cur > max_len) 
            { 
                max_len = cur; 
                max_line = line_no; 
            }
            lines++;
            line_no++;
            cur = 0;
        } else if (text[i] != '\r') 
        {   
            cur++;
        }
    }
    
    if (cur > 0) {
        if (cur > max_len) 
        { 
            max_len = cur; 
            max_line = line_no; 
        }
        lines++;
    }

    printf("Ֆայլի չափը՝ %d բայթ\n", size);
    printf("Տողեր՝ %d\n", lines);
    if (lines > 0)
        printf("Ամենաերկար տողը՝ %d-րդը (%d սիմվոլ)\n", max_line, max_len);

    free(text);
    return 0;
}



