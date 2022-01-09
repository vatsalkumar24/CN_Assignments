#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h>

int main()
{
    int fin = open("f1.txt", O_RDONLY);
    int fout = open("f2.txt", O_WRONLY);

    char c;
    while(read(fin,&c,1))
    {
        
        if(c >= 'a' && c <='z')
        {
            char temp[10]; temp[0] = c - 32;
            write(fout, temp, 1);
        }
        else {
            char temp[10]; temp[0] = c;
            write(fout, temp, 1);
        }
    }
    close(fin);
    close(fout);
}