#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <bits/stdc++.h>
using namespace std;
#define PORT 4848 

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
	if(getpeername(sfd, (struct sockaddr *)&c_addr, (socklen_t *)&addrlen) == -1)
	{	char foreign[16];
		inet_ntop(AF_INET, &c_addr.sin_addr, foreign, sizeof(foreign));
		int client_port = ntohs(c_addr.sin_port);
		cout << "Foreign IP: " << foreign << endl;
		cout << "Foreign Port: " << client_port << endl;
	}
	cout<<"Enter message: ";
	cin.getline(buffer,100);
	send(sfd, buffer,sizeof(buffer), 0);

    close(sfd);

    return 0;
} 