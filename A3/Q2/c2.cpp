#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include<iostream>
using namespace std;

void * sendthread(void *arg)
{
	while(true)
	{
		int ffd=open("server",O_WRONLY);
		char s[100];
		cout<<"\nClient 2, what would u send: ";
		cin.getline(s,100);
		if(strlen(s) == 0) break;
		char s1[100] = "\nC2:- ";
		strcat(s1,s);
		write(ffd,s1,strlen(s1));
		close(ffd);
	}
}
void * recievethread(void *arg)
{
	while(true)
	{
		int ffd=open("clnt2",O_RDONLY);
		char s[100];
		read(ffd, s, 100); 
		if(strlen(s) == 0) break;
		cout<<endl<<s<<endl;
		close(ffd);
	}
}
int main()
{
	pthread_t t1,t2;
	mkfifo("server",0666);
	mkfifo("clnt2",0666);
	pthread_create(&t1,NULL,recievethread,NULL);
	pthread_create(&t2,NULL,sendthread,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}