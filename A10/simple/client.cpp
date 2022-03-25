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

int main() 
{
    ACE_INET_Addr s_addr(PORT,INADDR_LOOPBACK);
    ACE_SOCK_Connector conn;
    ACE_SOCK_Stream sfd;
    char buffer[100];

    if(conn.connect(sfd,s_addr)<0)
    {
        cout<<"connect error"<<endl;
    }
    else cout<<"Connection succesfull!"<<endl;
    cout<<"Enter message for server: ";
    cin.getline(buffer,100);
    if(sfd.send_n(buffer,100)<0)
    {
        cout<<"send_n error"<<endl;
    }
    else cout<<"Message Sent!"<<endl;
    sfd.close();
}