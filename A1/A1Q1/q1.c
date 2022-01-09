#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h>
char *itoa(int num, char *str)
{
    if(str == NULL)
    {
            return NULL;
    }
    sprintf(str, "%d", num);
    return str;
}
int main() {
    int fin1,fin2,fout;
    fin1 = open("f1.txt",O_RDONLY);
    fin2 = open("f2.txt",O_RDONLY);
    fout = open("f3.txt",O_WRONLY);

    int num1[100],num2[100];
    char c,d,i=0,j=0;
    while(read(fin1,&c,1))
    {
        if(c!=' ')
        num1[i++] = (int)c - (int)'0';
    }
    while(read(fin2,&d,1))
    {
        if(d!=' ')
        num2[j++] = (int)d - (int)'0';
    }
    //for(int x=0; x<i; x++) printf("%d ", num1[x]);
    //for(int x=0; x<j; x++) printf("%d ", num2[x]);

    int x =0, y=0;
    while(x<i && y<j)
    {
        if(num1[x] < num2[y])
        {
            char temp[10];
            itoa(num1[x++],temp);
            write(fout,temp,strlen(temp));
        }
        else{
            char temp[10];
            itoa(num2[y++],temp);
            write(fout,temp,strlen(temp));
        }
        write(fout," ", 1);
    }
    while(x<i)
    {
        char temp[10];
        itoa(num1[x++],temp);
        write(fout,temp,1);
    }
    while(y<j)
    {
        char temp[10];
            itoa(num2[y++],temp);
            write(fout,temp,1);
    }
    close(fin1);
    close(fin2);
    close(fout);
}
