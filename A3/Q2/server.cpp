#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include<iostream>
using namespace std;
void *sendthread(void *arg)	
{
	while(true)
	{
		int fd = open("server", O_RDONLY);
		char buff[100];
		read(fd, buff, 100); 
		close(fd);
        if(strlen(buff))
        {
        	char s[] = "Msg from Server => ";
			strcat(s,buff);
    	    int cd1=open("clnt1",O_WRONLY);
			write(cd1,s,strlen(s));
			int cd2=open("clnt2",O_WRONLY);
			write(cd2,s,strlen(s));
			int cd3=open("clnt3",O_WRONLY);
			write(cd3,s,strlen(s));
			close (cd1);
			close (cd2);
			close (cd3);
		}
	}
}
int main()
{
	pthread_t t1;
	mkfifo("server",0666);
	mkfifo("clnt1",0666);
	mkfifo("clnt2",0666);
	mkfifo("clnt3",0666);
	pthread_create(&t1,NULL,sendthread,NULL);
	pthread_join(t1,NULL);
}