#include <unistd.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <bits/stdc++.h>
#include <arpa/inet.h>
using namespace std;
#define PORT 2424 
int main() 
{ 
	int sfd = 0; 
	struct sockaddr_in c_addr; 
	char buffer[100] = {0}; 
	if ((sfd= socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		cout<<"Socket creation failure!"<<endl; 
		return -1; 
	} 

	c_addr.sin_family = AF_INET; 
	c_addr.sin_port = htons(PORT); 
	if(inet_pton(AF_INET, "127.0.0.1", &c_addr.sin_addr)<=0) 
	{ 
		cout<<"Invalid Adress!"<<endl; 
		return -1; 
	} 
	while (connect(sfd, (struct sockaddr *)&c_addr, sizeof(c_addr)) < 0) 
	{ 
		cout<<"Socket Connection Failure!"<<endl; 
		sleep(2);
	}
	cout<<"Connection succcessfully!"<<endl;
	
    int fd = open("P.cpp",O_RDONLY);
    char input;
    string in;
    while(read(fd,&input,1)>0)
    {
        in+=input;
    }
    in.push_back('\0');
    send(sfd, in.c_str(),in.size(),0);
    cout<<"P.cpp sent successfully"<<endl;
    cout<<"waiting for test result...."<<endl;
    read(sfd,&buffer,100);
    cout<<"Test case "<<buffer<<endl;
    close(sfd);

    return 0;
} 