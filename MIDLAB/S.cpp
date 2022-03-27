#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/tcp.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <bits/stdc++.h>
#include <poll.h>
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
    cout<<"In Server S."<<endl;
    // three fifo for P1 P2 P3
    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);
    mkfifo("fifo3", 0666);

    int size = 3;
    struct pollfd pfd[size];

    pfd[0].fd = open("fifo1", O_RDWR);
    pfd[0].events = POLLIN;
    pfd[0].revents = 0;

    pfd[1].fd = open("fifo2", O_RDWR);
    pfd[1].events = POLLIN;
    pfd[1].revents = 0;

    pfd[2].fd = open("fifo3", O_RDWR);
    pfd[2].events = POLLIN;
    pfd[2].revents = 0;

    // sfd for accepting any incoming clients using BSD
    int sfd, nsfd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[100] = {0};

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    cout << "Created socket.." << endl;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // binding the address to sfd
    if (bind(sfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    cout << "Binded socket to address.." << endl;

    // listen to the socket, with maximum buffer for clients
    if (listen(sfd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    cout << "Server listening on port " << PORT << endl;
    
    //Unix SFD creation for forwarding FD to E
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
    
    // Raw socket creation for notifying A1 A2 A3 A4
    int rsfd;
    if ((rsfd = socket(AF_INET, SOCK_RAW, 2)) < 0)
    {
        perror("Raw Socket creation failed!");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    // polling for p1 p2 P3
    cout << "Starting Poll" << endl;
    while (1)
    {
        int status = poll(pfd, size, -1);
        if (status == 0)
        {
            cout << "Poll timed out.." << endl;
            continue;
        }
        else if (status < 0)
        {
            cout << "poll failed..." << endl;
            perror("poll");
            exit(1);
        }
        for (int i = 0; i < size; i++)
        {
            if (pfd[i].revents & POLLIN)
            {
                
                char buff[128];
                read(pfd[i].fd, buff, 128);
                cout << buff << endl;
                string s(buff);
                // if P1 | P2 sends data
                if(i == 0 || i == 1)
                    sendto(rsfd, s.c_str(), s.size(),0, (const struct sockaddr*)&s_addr, sizeof(s_addr));
                else{  //P3 sends data
                    cout<<"Waiting for clients."<<endl;
                    nsfd = accept(sfd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
                    cout<<"Client accepted. now forwarding to new E(server)"<<endl;
                    if(send_fd(nusfd,nsfd)<=0)
                    {
                        perror("Sending SFD failure!");
                        exit(EXIT_FAILURE);
                    }
                    cout<<"SFD passed succcessfully to Echo Server (E)!"<<endl;
                }
                pfd[i].revents = 0;
            }
        }
    }
}