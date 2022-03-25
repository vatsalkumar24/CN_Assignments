#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<pthread.h>
#include<ctype.h> 
#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;
#define PORT1 10001
#define PORT2 10002
#define PORT3 10003
struct thread_fd {
    int sfd;
};

void* read_send(void *args){
    
    struct thread_fd * nsfd = (struct thread_fd *) args;
    int nsfd2 = nsfd->sfd;
    cout<<nsfd2<<endl;
    char buffer[100];
        recv(nsfd2,buffer,100,0);
        cout<<"Client 2: "<<buffer<<endl;
        cout<<"Message for client 2: ";
        cin.getline(buffer,100);
        send(nsfd2,buffer,100,0);
}
int main(){

    int sfd1,sfd2,sfd3;
    sfd1 = socket(AF_INET,SOCK_STREAM,0);
    sfd2 = socket(AF_INET,SOCK_STREAM,0);
    sfd3 = socket(AF_INET,SOCK_DGRAM,0);  
	if(sfd1 < 0) cout<<"sfd1 failure!";
	if(sfd2 < 0) cout<<"sfd2 failure!";
	if(sfd3 < 0) cout<<"sfd3 failure!";

    struct sockaddr_in addr1;
    addr1.sin_family = AF_INET;
    addr1.sin_port = htons(PORT1);
    addr1.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(sfd1,(struct sockaddr*) &addr1,sizeof(addr1))<0)
    	{ 
		perror("Socket 1 Binding failure!"); 
		exit(EXIT_FAILURE); 
	}
    struct sockaddr_in addr2;
    addr2.sin_family = AF_INET;
    addr2.sin_port = htons(PORT2);
    addr2.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(sfd2,(struct sockaddr*) &addr2,sizeof(addr2))<0)
    { 
		perror("Socket 2 Binding failure!"); 
		exit(EXIT_FAILURE); 
	}

    struct sockaddr_in addr3;
    addr3.sin_family = AF_INET;
    addr3.sin_port = htons(PORT3);
    addr3.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(sfd3,(struct sockaddr*) &addr3,sizeof(addr3))<0)
    { 
		perror("Socket 3 Binding failure!"); 
		exit(EXIT_FAILURE); 
	}
    
    if(listen(sfd1,10)<0)
    {
        perror("Listening Failure!"); 
		exit(EXIT_FAILURE);
    }
    if(listen(sfd2,10)<0)
    {
        perror("Listening Failure!"); 
		exit(EXIT_FAILURE);
    }
    int nsfd1;

    int addr_len;
    struct sockaddr_in6 client_addr;
    addr_len = sizeof(client_addr);
    int nsfd2;

    pthread_t pt;
    fd_set rfds;    
    int maxfd=max(max(sfd1,sfd2),sfd3)+1;
    FD_ZERO(&rfds);
    while(1){
        FD_SET(sfd1,&rfds);
        FD_SET(sfd2,&rfds);
        FD_SET(sfd3,&rfds);
        int sefd = select(maxfd,&rfds,NULL,NULL,NULL);
        if(FD_ISSET(sfd1, &rfds))
        {
            int nsfd1 = accept(sfd1,NULL,NULL);
            if(nsfd1 < 0)
            {
                perror("Socket accept failure!"); 
			    exit(EXIT_FAILURE); 
            }
            int c = fork();
            if(c == 0)
            {
                close(sfd1);
                dup2(nsfd1,0);
                dup2(nsfd1,1);
                system("g++ s1.cpp -o s1");
                execv("./s1", NULL);
            }
            else{
                close(nsfd1);
            }
        }
        if(FD_ISSET(sfd2, &rfds)){
            int nsdf2 = accept(sfd2,NULL,NULL);
            struct thread_fd nsfd;
            nsfd.sfd = nsdf2;
            cout<<nsdf2<<endl;
            pthread_create(&pt,NULL,&read_send,(void*)&nsdf2);
            pthread_join(pt,NULL);
        }
        if (FD_ISSET(sfd3, &rfds))
        {
            while(1){
            int rcv;
            char buffer[100];
            rcv = recvfrom(sfd3, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr,(socklen_t *)&addr_len);
            if (rcv < 0)
            {
                perror("connectionless recv failure!");
                break;
            }
            cout<<"Message from Client 3: "<<buffer<<endl;
            cout<<"Enter message for Client 3: ";
            char *buffer2 = new char[100];
            cin.getline(buffer2,100);
            sendto(sfd3,(const char *)buffer2,strlen(buffer2), MSG_CONFIRM,(const struct sockaddr *)&client_addr,addr_len);
            }
        }
        
        
    }
    return 0;
}