
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
   int c;
   printf("1. Parent Process.\n");
   c = fork();
   if(c>0)
   {
      printf("2. Parent Process.\n");
      char *args[]={"./p3",NULL};
      execv(args[0],args);
      waitpid(c,NULL,0);     
   }
   else{
      printf("3. Child Process.\n");
      char *args[]={"./p2",NULL};
      execv(args[0],args);
   }
   printf("\n\n");
   return 0;
}