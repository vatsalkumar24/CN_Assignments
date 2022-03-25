#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <bits/stdc++.h>
using namespace std;
#define PORT 10002 

int main() 
{ 
	int sfd = 0; 
	struct sockaddr_in c_addr; 
	int addrlen = sizeof(c_addr); 
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
	cout<<"Enter message: ";
	cin.getline(buffer,100);
	int valread = send(sfd, buffer,sizeof(buffer), 0);
    cout<<valread<<endl;
    cout<<"Wating for message from SERVER S..... "<<endl;
    read(sfd,buffer,100);
    cout<<buffer<<endl;
    close(sfd);

    return 0;
} 