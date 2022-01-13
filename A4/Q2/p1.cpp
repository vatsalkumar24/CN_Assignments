#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include<bits/stdc++.h>
#include <poll.h>
using namespace std;
int main()
{
    struct pollfd pfds[3];
    mkfifo("FIFO2", 0777);
    mkfifo("FIFO3", 0777);
    mkfifo("FIFO4", 0777);
    while(1)
    {
        pfds[0].fd = open("FIFO2",O_RDONLY); pfds[0].events = POLLIN;
        pfds[1].fd = open("FIFO3",O_RDONLY); pfds[1].events = POLLIN;
        pfds[2].fd = open("FIFO4",O_RDONLY); pfds[2].events = POLLIN;

        poll(pfds,3,-1);
        int done = 0;
        for(int i=0; i<3; i++)
        {
            if(pfds[i].revents && POLLIN)
            {
                char s[100];
                int pos = read(pfds[i].fd,s,100);
                s[pos] ='\0';
                if(s[0] == 'b' && s[1] == 'y' && s[2] == 'e')
                {
                    cout<<"Process "<<i+2<<" exited"<<endl;
                    done++;
                    if(done == 3) exit(1);
                }
                else cout<<"Process "<<i+2<<": "<<s<<endl;
            }
            
            
        }
    }
}