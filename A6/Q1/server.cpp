#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <bits/stdc++.h>
#include <arpa/inet.h>
using namespace std;
#define PORT 4848
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
		perror("setsockopt"); 
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
	if(getsockname(sfd, (struct sockaddr *)&s_addr, (socklen_t *)&addrlen) !=-1)
    {
		char locall[16];
		inet_ntop(AF_INET, &s_addr.sin_addr, locall, sizeof(locall));
		int myPort = ntohs(s_addr.sin_port);
		cout << "Local IP: " << locall << endl;
		cout << "Local Port: " << myPort << endl;
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
		if(getpeername(nsfd, (struct sockaddr *)&s_addr, (socklen_t *)&addrlen) != -1)
        {
			char foreign[16];
			inet_ntop(AF_INET, &s_addr.sin_addr, foreign, sizeof(foreign));
			int client_port = ntohs(s_addr.sin_port);
			cout << "Foreign IP: " << foreign << endl;
			cout << "Foreign Port: " << client_port << endl;
		}
		if(read(nsfd,buffer,sizeof(buffer)) == 0)
		{
			cout<<"Connection turned down!"<<endl;
			close(nsfd);
			continue;
		}
		cout<<"Client's message: "<<buffer<<endl;
		close(nsfd);
	}	
	close(sfd);
	return 0; 
} 
