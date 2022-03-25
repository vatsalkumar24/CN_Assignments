#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
#define PORT 4040
using namespace std;
int main()
{
    int sfd;
    struct sockaddr_in addr;
    int len = sizeof(addr); 
	char buffer[100];
    if ((sfd= socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		cout<<"Socket creation failure!"<<endl; 
		return -1; 
	}

    addr.sin_family = AF_INET; 
	addr.sin_port = htons(PORT); 
	if(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)<=0) 
	{ 
		cout<<"Invalid Adress!"<<endl; 
		return -1; 
	} 
    while (connect(sfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
	{ 
		cout<<"Socket Connection Failure!"<<endl; 
		sleep(2);
	}
    char service[3];
    cout<<"sf1 or sf2: ";
    cin>>service;
	send(sfd, service ,sizeof(service), 0);
    cout<<"Service Requested succcessfully"<<endl;
    cout<<"Enter message: ";
	strcpy(buffer,"client1");
	send(sfd, buffer,sizeof(buffer), 0);
    cout<<"Message sent succcessfully"<<endl;
    memset(buffer,'\0',sizeof(buffer));
    recv(sfd,buffer,sizeof(buffer),0);
    cout<<"Message from Server: "<<buffer<<endl;

    return 0;
}   
