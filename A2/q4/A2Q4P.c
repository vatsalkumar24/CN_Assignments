#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pfd[2];
    pipe(pfd);
    int c = fork();
    if(c>0)
    {
        
    }
}