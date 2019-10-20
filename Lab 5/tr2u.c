#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Not enough arguments!\n");
        exit(1);
    }
    
    char* from = argv[1];
    char* to = argv[2];
    
    if (strlen(from) != strlen(to))
    {
        fprintf(stderr, "Both arguments should be the same length!\n");
        exit(1);
    }
    
    size_t i;
    size_t j;
    for(i = 0; i < strlen(from); i++)
    {
        for(j = i + 1; j < strlen(from); j++)
        {
            if(from[i] == from[j])
            {
                fprintf(stderr, "No duplicate characters!\n");
                exit(1);
            }
        }
    }
    
    char buffer[1];
    size_t checkEnd = read(0, buffer, 1);
    while (!!checkEnd)
    {
        for(i = 0; i < strlen(from); i++)
        {
            if(buffer[0] == from[i])
            {
                buffer[0] = to[i];
                break;
            }
        }
        write(1, buffer, 1);
        checkEnd = read(0, buffer, 1);
    }
    return 0;
}