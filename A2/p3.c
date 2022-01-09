#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    printf("1");
    int c = fork();
    if(c>0)
    {
        printf("2"); 
        wait(NULL);
    }
    else printf("3");
    return 0;
}