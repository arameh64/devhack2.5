#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

char* find_path(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            continue; 
        }
        else
        {
            return argv[i];
        }
    }
    return NULL; 
}


int main(int argc, char** argv)
{


}