#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <bits/stdc++.h>
using namespace std;
#define PORT 10003 

int main() 
{ 
	int sfd = 0; 
	struct sockaddr_in c_addr; 
	int addrlen = sizeof(c_addr); 
	char buffer[100] = {0}; 
	if ((sfd= socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
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
	sendto(sfd, buffer,sizeof(buffer), 0,(const struct sockaddr*)&c_addr,sizeof(c_addr));
    cout<<"Wating for message from SERVER 1..... "<<endl;
    char buffer2[100]; memset(buffer2, 0, sizeof(buffer2));
    recvfrom(sfd,buffer2,100,0,(struct sockaddr*)&c_addr,(socklen_t *)addrlen);
    cout<<buffer2<<endl;
    close(sfd);

    return 0;
} 