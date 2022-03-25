#include <bits/stdc++.h>
#include <unistd.h> 
#include<fcntl.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <arpa/inet.h> 
#include <sys/un.h>
#include <sys/wait.h>
using namespace std;
#define PORT 4040
int send_fd(int socket, int fd_to_send)  
{  
    struct msghdr socket_message;  
    struct iovec io_vector[1];  
    struct cmsghdr *control_message = NULL;  
    char message_buffer[1];  

    /* storage space needed for an ancillary element with a paylod of  length is CMSG_SPACE(sizeof(length)) */  
    char ancillary_element_buffer[CMSG_SPACE(sizeof(int))]; 
    int available_ancillary_element_buffer_space;  

    /* at least one vector of one byte must be sent */  
    message_buffer[0] = 'F'; 
    io_vector[0].iov_base = message_buffer;  
    io_vector[0].iov_len = 1;  

    /* initialize socket message */  
    memset(&socket_message, 0, sizeof(struct msghdr));  
    socket_message.msg_iov = io_vector;  
    socket_message.msg_iovlen = 1;  
    
    /* provide space for the ancillary data */  
    available_ancillary_element_buffer_space = CMSG_SPACE(sizeof(int));   memset(ancillary_element_buffer, 0,available_ancillary_element_buffer_space);  
    socket_message.msg_control = ancillary_element_buffer;   socket_message.msg_controllen = available_ancillary_element_buffer_space;  

    /* initialize a single ancillary data element for fd passing */ 
    control_message = CMSG_FIRSTHDR(&socket_message);  
    control_message->cmsg_level = SOL_SOCKET;  
    control_message->cmsg_type = SCM_RIGHTS;  
    control_message->cmsg_len = CMSG_LEN(sizeof(int));  
    *((int *) CMSG_DATA(control_message)) = fd_to_send;  
    return sendmsg(socket, &socket_message, 0);  
}  
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
    cout<<"Enter message: ";
	cin.getline(buffer,100);
	send(sfd, buffer,sizeof(buffer), 0);
    cout<<"Message sent succcessfully"<<endl;
    memset(buffer,'\0',sizeof(buffer));
    recv(sfd,buffer,sizeof(buffer),0);
    cout<<"Message from Server: "<<buffer<<endl;

    int usfd,nusfd; 
    struct sockaddr_un usfd_addr; 
    if((usfd = socket(AF_UNIX , SOCK_STREAM , 0))<0)
    {
        cout<<"Unix Socket creation failure!"<<endl; 
		return -1; 
    }
    bzero(&usfd_addr,sizeof(usfd_addr)); 
    usfd_addr.sun_family = AF_UNIX;  
	strcpy(usfd_addr.sun_path, "client1");  
	unlink("client1");  

    if(bind(usfd, (struct sockaddr *)&usfd_addr, sizeof(struct sockaddr_un))<0) 
    {
        perror("Unix Socket Binding failure!"); 
		exit(EXIT_FAILURE); 
    }
    if(listen(usfd,3)<0)
    {
        perror("Listening Failure!"); 
		exit(EXIT_FAILURE);
    }

    nusfd = accept(usfd,NULL,NULL);
    if(nusfd<0)
	{
	    perror("Accept failure!"); 
		exit(EXIT_FAILURE); 
	}
    if(send_fd(nusfd,sfd)<=0)
    {
        perror("Sending SFD failure!");
        exit(EXIT_FAILURE);
    }
    cout<<"SFD passed succcessfully to client 2!"<<endl;
}