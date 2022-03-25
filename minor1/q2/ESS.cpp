#include <bits/stdc++.h>
#include <unistd.h> 
#include<fcntl.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <arpa/inet.h> 
using namespace std;
#define PORT 4040
int main()
{
    int sfd,nsfd,opt = 1; char buffer[100];
    struct sockaddr_in addr; socklen_t len = sizeof(addr);
	
    if ((sfd= socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		cout<<"Socket creation failure!"<<endl; 
		return -1; 
	}
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    addr.sin_family=AF_INET;
	addr.sin_port=htons(PORT);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(bind(sfd,(struct sockaddr*) &addr,sizeof(addr))<0)
    { 
		perror("Socket Binding failure!"); 
		exit(EXIT_FAILURE); 
	}
    if(listen(sfd,3)<0)
    {
        perror("Listening Failure!"); 
		exit(EXIT_FAILURE);
    }
    nsfd=accept(sfd,(struct sockaddr* )&addr,&len);
	if(nsfd<0)
	{
	    perror("Accept failure!"); 
		exit(EXIT_FAILURE); 
	}
    cout<<"Server running succesfully "<<endl;
    while(1)
	{
        recv( nsfd,buffer,sizeof(buffer),0); 
        cout<<"Message Recieved: "<<buffer<<endl;
        memset(buffer,'\0',sizeof(buffer));
        cout<<"Message from Server: "; cin.getline(buffer,100);
        send(nsfd,buffer,sizeof(buffer),0);
        memset(buffer,'\0',sizeof(buffer));
	}
	return 0; 
}