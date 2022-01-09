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
		char msg1[100]; char temp[20];
        while(1)
        {
            printf("P1 writing to P2: "); 
            fgets(msg1, sizeof(msg1), stdin);
            if(strlen(msg1) == 0) break;
            write(pfd1[1],msg1,sizeof(msg1));
            read(pfd2[0],temp,sizeof(temp));
            if(strlen(temp) == 0) break;
            printf("P1 reading from pipe: %s\n",temp);
        }
        close(pfd1[1]);
        close(pfd2[0]);
        exit(0);
	}
	else{
		close(pfd1[1]);
        close(pfd2[0]);

		dup2(0,10);
		dup2(1,11);
		dup2(pfd1[0],0);
		dup2(pfd2[1],1);

		char *args[]={"./p2",NULL};
      	execv(args[0],args);
	}
}