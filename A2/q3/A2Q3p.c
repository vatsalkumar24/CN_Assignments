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
      char *args[]={"./p2",NULL};
      execv(args[0],args);
      printf("4. Post Parent Process.\n");
   }
   else{
      printf("3. Child Process.\n");
   }
   printf("\n\n");
   return 0;
}