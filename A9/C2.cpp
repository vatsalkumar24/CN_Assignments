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
int recv_fd(int socket)  
{  
	int sent_fd, available_ancillary_element_buffer_space;   struct msghdr socket_message;  
	struct iovec io_vector[1];  
	struct cmsghdr *control_message = NULL;  
	char message_buffer[1];  
	char ancillary_element_buffer[CMSG_SPACE(sizeof(int))];  
	 
	/* start clean */  
	memset(&socket_message, 0, sizeof(struct msghdr));  
	memset(ancillary_element_buffer, 0, CMSG_SPACE(sizeof(int)));  
	
	/* setup a place to fill in message contents */  
	io_vector[0].iov_base = message_buffer;  
	io_vector[0].iov_len = 1;  
	socket_message.msg_iov = io_vector;  
	socket_message.msg_iovlen = 1;  
	
	/* provide space for the ancillary data */  
	socket_message.msg_control = ancillary_element_buffer;   socket_message.msg_controllen = CMSG_SPACE(sizeof(int));  
	if(recvmsg(socket, &socket_message, MSG_CMSG_CLOEXEC) < 0)   return -1;  
	if(message_buffer[0] != 'F')  
	{  
		/* this did not originate from the above function */
        return -1;  
	}  
	if((socket_message.msg_flags & MSG_CTRUNC) == MSG_CTRUNC) 
    {
        /* we did not provide enough space for the ancillary element array */   return -1;  
	} 
	 
	/* iterate ancillary elements */  
	for(control_message = CMSG_FIRSTHDR(&socket_message); control_message != NULL;control_message = CMSG_NXTHDR(&socket_message, control_message)) 
    {  
		if( (control_message->cmsg_level == SOL_SOCKET) &&  
		(control_message->cmsg_type == SCM_RIGHTS) )  
		{  
		    sent_fd = *((int *) CMSG_DATA(control_message));  
		    return sent_fd;  
		}  
	}  
	return -1;  
}
int main()
{
    int sfd; char buffer[100];
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

    if(connect(usfd,(struct sockaddr *)&usfd_addr,sizeof(struct sockaddr_un))<0) 
    {
        perror("Unix Socket Connection failure!"); 
		exit(EXIT_FAILURE); 
    }
    if((sfd = recv_fd(usfd))<0)
    {
        perror("Receiving SFD failure!");
        exit(EXIT_FAILURE);
    }
    cout<<"SFD received succesfully from client 1!"<<endl;
    cout<<"Enter message: ";
	cin.getline(buffer,100);
	send(sfd, buffer,sizeof(buffer), 0);
    cout<<"Message sent succcessfully"<<endl;
    memset(buffer,'\0',sizeof(buffer));
    recv(sfd,buffer,sizeof(buffer),0);
    cout<<"Message from Server: "<<buffer<<endl;

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
        perror("Sending FD failure!");
        exit(EXIT_FAILURE);
    }
    cout<<"SFD passed succcessfully to client 3!"<<endl;
    return 0;
}