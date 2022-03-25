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
    ACE_INET_Addr c_addr;
    ACE_SOCK_Acceptor acc(s_addr);
    ACE_SOCK_Stream sfd;
    char buffer[100];
    cout<<"Server started ...."<<endl;
    
    while(1)
    {
        acc.accept(sfd);
        cout<<"Connection made!"<<endl;
        if(sfd.recv_n(buffer,100)<0)
        {
            cout<<"recv_n error"<<endl;
        }
        else cout<<"Client's Message: "<<buffer<<endl;
        sfd.close();
    }
}

