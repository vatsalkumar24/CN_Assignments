#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    printf("I am Process P2.\n");
    int rd = dup(0);
    int wd = dup(1);

    dup2(11,1);
    dup2(10,0);

    while(1){
        char temp[100];
        read(rd,temp,sizeof(temp));
        if(strlen(temp) == 0) break;
        printf("P2 reading from pipe: %s\n",temp);
        char msg[100];
        printf("P2 writing to P1: "); 
        fgets(msg, sizeof(msg),stdin);
        write(wd,msg,sizeof(msg));
        if(strlen(msg) == 0) break;
    }
    close(rd);
    close(wd);
    exit(0);
}