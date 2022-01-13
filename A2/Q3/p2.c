#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    //printf("I am Process P2.\n");
    int rd = dup(0);
    int wd = dup(1);

    dup2(11,1);
    dup2(10,0);

    int pfd1[2];
    int pfd2[2];

    pipe(pfd1);
    pipe(pfd2);
    int c = fork();
    if(c>0)
    {
        close(pfd1[0]);
        close(pfd2[1]);
        while(1){
            char temp[100];
            read(rd,temp,sizeof(temp));
            if(strlen(temp) == 0) break;
            printf("P2 reading from pipe of P1: %s\n",temp);
            printf("P2 forwarding to P3 ....\n"); 
            write(pfd1[1],temp,sizeof(temp));

            char temp2[100];
            read(pfd2[0],temp2,sizeof(temp2));
            if(strlen(temp2) == 0) break;
            printf("P2 reading from pipe of P3: %s\n",temp2);
            printf("P2 forwarding to P1 ....\n "); 
            write(wd,temp2,sizeof(temp2));
            
        }
        close(pfd1[1]);
        close(pfd2[0]);
    }
    else{
        close(pfd1[1]);
        close(pfd2[0]);

		dup2(0,10);
		dup2(1,11);
		dup2(pfd1[0],0);
		dup2(pfd2[1],1);

		char *args[]={"./p3",NULL};
      	execv(args[0],args);
    }
    close(rd);
    close(wd);
    
}