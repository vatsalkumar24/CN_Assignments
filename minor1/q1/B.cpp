#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <poll.h>
#define PORT 5050
using namespace std;
struct msg{
    long type;
    char text[100];
};

void sf1(int nsfd)
{
    char buffer[100];
    while (1)
    {
        read(nsfd, buffer, 100);
        cout << "Client Msg: " << buffer << endl;
        string s_msg = "served client with sf1 service";
        strcpy(buffer, s_msg.c_str());
        send(nsfd, buffer, s_msg.size(), 0);
        memset(buffer, 0, 100);
    }
}
void sf2(int nsfd)
{
    char buffer[100];
    while (1)
    {
        read(nsfd, buffer, 100);
        cout << "Client Msg: " << buffer << endl;
        string s_msg = "served client with sf2 service";
        strcpy(buffer, s_msg.c_str());
        send(nsfd, buffer, s_msg.size(), 0);
        memset(buffer, 0, 100);
    }
}
int main()
{
    int key = ftok("msgq", 65);
    int msqid = msgget(key, 0666 | IPC_CREAT);
    struct msg m;
    memset(m.text,0,sizeof(m.text));
    msgrcv(msqid, &m, sizeof(m), 0, 0);
    cout<<m.text<<endl;
    int send_pid=atoi(m.text);
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(sfd, (struct sockaddr *)&address, sizeof(address));
    listen(sfd,3);

    while(1)
    {
        int nsfd = accept(sfd,NULL,NULL);
        if(nsfd<0)
        {
            cout<<"accept failure!"<<endl;
            exit(EXIT_FAILURE);
        }
        char c[100];
        if(read(nsfd,&c,100)==0)
        {
            continue;
        }
        if(strcmp(c,"sf1") == 0)
        {
            sf1(nsfd);
            kill(send_pid,SIGUSR1);
        }
        else{
            sf2(nsfd);
            kill(send_pid,SIGUSR2);
        }
    }
}
