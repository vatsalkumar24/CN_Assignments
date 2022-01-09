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

    char c, temp[50]; int x = 0,count=0;
    while(read(fin,&c,1))
    {
        if((c>='a' && c<='z') || (c>='A' && c<='Z'))
        {
            char temp[10];
            temp[0] = c;
            write(fout,temp,1);
            count++;
        }
        else{
            temp[x++] = c;
        }
    }
    lseek(fout,1000 - count,SEEK_CUR);
    count=0;
    while(count<x)
    {
        write(fout,&temp[count],1);
        count++;
    }
    close(fin);
    close(fout);
}