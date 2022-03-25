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
#include <ace/SOCK_Stream.h>
#include <ace/UNIX_Addr.h>
#include <ace/OS.h>
#include <ace/SOCK_Dgram.h>
#include <ace/OS_NS_unistd.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h>
#include <ace/Task.h>
#include <ace/Future.h>
#include <ace/Auto_Ptr.h>
#include <ace/config-lite.h>
using namespace std;

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
    ACE_UNIX_Addr s_addr("ace.sock");
    ACE_SOCK_Acceptor acc(s_addr);
    ACE_SOCK_Stream sfd;
    char buffer[100];
    cout<<"Server running succesfully"<<endl;
    
    while(1)
    {
        acc.accept(sfd);
        cout<<"Connection made with client!"<<endl;
        int recvfd = recv_fd(sfd.get_handle());
        cout<<"FD recieved!"<<endl;
        cout<<"Reading data using recieved fd: ";
        char c;
        while(read(recvfd,&c,1))
        {
            cout<<c;
        }
        sfd.close();
    }
}
