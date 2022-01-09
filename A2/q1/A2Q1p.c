
#include <stdio.h>
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
      wait(NULL);
   }
   else{
      printf("3. Child Process.\n");
      char *args[]={"./p2",NULL};
      execv(args[0],args);

   }
   printf("\n\n");
   return 0;
}