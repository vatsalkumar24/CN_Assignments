#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pfd1[2],pfd2[2];
    int x = pipe(pfd1), y = pipe(pfd2);
    char msg1[100] = "hello world!";
    char msg2[100] = "hi universe!";
    char temp[20];
    if(x == -1){
        printf("Pipe1 creation failed.!\n");
        return 0;
    }
    if(y == -1){
        printf("Pipe2 creation failed.!\n");
        return 0;
    }
    int c = fork();
    if(c>0)
    {
        close(pfd1[0]);
        close(pfd2[1]);
        while(1)
        {
            printf("P writing to P': "); 
            fgets(msg1, sizeof(msg1), stdin);
            if(strlen(msg1) == 0) break;
            write(pfd1[1],msg1,sizeof(msg1));
            read(pfd2[0],temp,sizeof(temp));
            if(strlen(temp) == 0) break;
            printf("P reading from pipe: %s\n",temp);
        }
        
    }
    else{
        close(pfd1[1]);
        close(pfd2[0]);
        while(1)
        {
            read(pfd1[0],temp,sizeof(temp));
            if(strlen(temp) == 0) break;
            printf("P' reading from pipe: %s\n",temp);
            printf("P' writing to P: "); 
            fgets(msg2, sizeof(msg2), stdin);
            if(strlen(msg2) == 0) break;
            write(pfd2[1],msg2,sizeof(msg2));
            
        }
    }
    return 0;
}