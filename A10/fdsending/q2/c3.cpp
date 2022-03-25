#include <stdio.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/select.h>
#include <string.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Connector.h>
#include <ace/UNIX_Addr.h>
#include <ace/SOCK_Stream.h>
#include <ace/OS.h>
#include <ace/SOCK_Dgram.h>
#include <ace/OS_NS_unistd.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h>
#include <ace/Task.h>
#include <ace/Future.h>
#include <ace/Auto_Ptr.h>
#include <ace/config-lite.h>
#define PORT 4040
using namespace std;

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
    
    ACE_UNIX_Addr s_addr("ace2.sock");
    ACE_SOCK_Connector conn;
    ACE_SOCK_Stream sfd;
    char buffer[100];

    if(conn.connect(sfd,s_addr)<0)
    {
        cout<<"connect error"<<endl;
    }
    else cout<<"Connection succesfull!"<<endl;

    int recvsfd = recv_fd(sfd.get_handle());
    cout<<"SFD recived from Client 2"<<endl;

    cout<<"Enter message: ";
	cin.getline(buffer,100);
	send(recvsfd, buffer,sizeof(buffer), 0);
    cout<<"Message sent succcessfully"<<endl;
    memset(buffer,'\0',sizeof(buffer));
    recv(recvsfd,buffer,sizeof(buffer),0);
    cout<<"Message from Server: "<<buffer<<endl;

    ACE_UNIX_Addr s_addr1("ace3.sock");
    ACE_SOCK_Acceptor acc1(s_addr1);
    ACE_SOCK_Stream sfd1;
    cout<<"Client 2 server running succesfully"<<endl;
    while(1)
    {
        acc1.accept(sfd1);
        cout<<"Connection made with client4!"<<endl;
        send_fd(sfd1.get_handle(),recvsfd);
        cout<<"fd sent!"<<endl;
    }
    sfd1.close();
}