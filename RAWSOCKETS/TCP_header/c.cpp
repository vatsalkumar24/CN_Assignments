#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <bits/stdc++.h>
#include <sys/un.h>
using namespace std;

int main(){
    int rsfd = socket(AF_INET, SOCK_RAW, 2);
    char buffer[100];
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(rsfd < 0){
        perror("socket creation failure!");
        exit(1);
    }
    char myIP[16];
    socklen_t len = sizeof(addr);
    getsockname(rsfd, (struct sockaddr *) &addr, &len);
    inet_ntop(AF_INET, &addr.sin_addr, myIP, sizeof(myIP));
    unsigned int myPort = ntohs(addr.sin_port);
    cout<<"Connected to Server"<<endl;
    while(1){

        cout<<"Send message to server: ";
        cin.getline(buffer, sizeof(buffer));
        sendto(rsfd, buffer, 100, 0, (struct sockaddr *)&addr, sizeof(addr));
    }
}