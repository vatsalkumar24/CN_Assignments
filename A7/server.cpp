#include <unistd.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/wait.h>
using namespace std;
#define PORT 2424
int main() 
{ 
	int sfd, nsfd; 
	struct sockaddr_in s_addr; 
	int opt = 1; 
	int addrlen = sizeof(s_addr); 
	char buffer[100] = {0}; 
	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 		
		cout<<"Socket creation failure!"<<endl; 
		exit(EXIT_FAILURE); 
	} 
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("Setting Up Socket failure!"); 
		exit(EXIT_FAILURE); 
	} 
	s_addr.sin_family = AF_INET; 
	s_addr.sin_addr.s_addr = INADDR_ANY; 
	s_addr.sin_port = htons( PORT ); 
	if (bind(sfd, (struct sockaddr *)&s_addr, sizeof(s_addr))<0) 
	{ 
		perror("Socket Binding failure!"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(sfd, 3) < 0) 
	{ 
		perror("Listening Failure!"); 
		exit(EXIT_FAILURE); 
	} 
	while(true){
		if ((nsfd = accept(sfd, (struct sockaddr *)&s_addr, (socklen_t*)&addrlen))<0) 
		{ 
			perror("Socket accept failure!"); 
			exit(EXIT_FAILURE); 
		} 
        int fd = open("p.cpp", O_RDWR | O_CREAT, 0777);
        char input;
        while(read(nsfd,&input,1)>0)
        {
            if(input == '\0') break;
            write(fd,&input,1);
        }
		cout<<"Client code recieved succesfully!"<<endl;
        system("g++ p.cpp -o p");
        cout<<"Cient code compiled succesfully"<<endl;

        int c = fork();
        if(c == 0)
        {
            int itfd = open("IT.txt", O_RDONLY);
            int poutfd = open("Pout.txt", O_RDWR);
            dup2(itfd, 0);
            dup2(poutfd, 1);
            execv("./p", NULL);
        }
        else{
            wait(NULL);
            int poutfd = open("Pout.txt",O_RDWR);
            int otfd = open("OT.txt",O_RDWR);
            string pouttext="",ottext=""; char ch;
            while(read(poutfd,&ch,1)>0)
            {
                pouttext+=ch;
            }
            while(read(otfd,&ch,1)>0)
            {
                ottext+=ch;
            }
            if(pouttext == ottext)
            {
                char result[] = "Passed";
                cout<<"Test Case "<<result<<endl;
                send(nsfd,&result,sizeof(result),0);
            }
            else{
                char result[] = "Failed";
                cout<<"Test Case "<<result<<endl;
                send(nsfd,&result,sizeof(result),0);
            }
        }
        
        close(nsfd);
        close(sfd);
	}	
	close(sfd);
	return 0; 
} 
