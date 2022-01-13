#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;
FILE* fd;
int ffd;
void * sendthread(void *arg)
{
        char s[100];
		while(1)
		{
			cout<<"\nenter send msg: ";
			cin.getline(s, 100);
			write(fileno(fd),s,strlen(s)+1);
            if(s[0] == '\0') break;
        }        
}
void * receivethread(void *arg)
{
		char s[100];
        ffd = open("green",O_RDONLY);
		while(1)
		{
			read(ffd, s, 100); 
			string str(s);
			if (s[0] == '\0'){ close(ffd); break;}
			if(str.length())
			{cout<<"recieved msg(capitalize): "<<str<<endl;}
            
		}
}
int main()
{
    fd = popen("./p2","w");
    mkfifo("green",0777);

    pthread_t t1,t2;
    pthread_create(&t2,NULL,sendthread,NULL);
    pthread_create(&t1,NULL,receivethread,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}