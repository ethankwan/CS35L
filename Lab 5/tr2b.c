/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
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
    
    int temp = getchar();
    while(temp != EOF)
    {
        for(i = 0; i < strlen(from); i++)
        {
            if(temp == from[i])
            {
                temp = to[i];
                break;
            }
        }
        putchar(temp);
        temp = getchar();
    }
    
    return 0;

}
