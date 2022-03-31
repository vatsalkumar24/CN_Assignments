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
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <semaphore.h>
#include <bits/stdc++.h>
#include <sys/un.h>
using namespace std;
int main(){
    int rsfd = socket(AF_INET, SOCK_RAW, 2);
    char buffer[2048];
    if(rsfd<0){
        perror("socket creation failure!");
        exit(1);
    }
    cout<<"Server started to print TCP Header: "<<endl;
    while(1){
        int n = recvfrom(rsfd, buffer, 2048, 0, NULL, NULL);
        if(n<0){
            perror("receiving data failure!");
            exit(1);
        }
        struct iphdr *ip = (struct iphdr *)(buffer);
        int iphdrlen = ip->ihl*4;
        struct tcphdr *tcp = (struct tcphdr*)(buffer + iphdrlen);
        cout<<"-----------------------TCP Header------------------------------"<<endl<<endl;
        cout<<"Source Port: "<<ntohs(tcp->source)<<endl;
        cout<<"Destination Port: "<<ntohs(tcp->dest)<<endl;
        cout<<"Sequence Number: "<<ntohl(tcp->seq)<<endl;
        cout<<"Acknowledgement Number: "<<ntohl(tcp->ack_seq)<<endl;
        cout<<"Header Length: "<<tcp->doff<<endl;
        cout<<"Urgent Flag: "<<tcp->urg<<endl;
        cout<<"Acknowledgement Flag: "<<tcp->ack<<endl;
        cout<<"Push Flag: "<<tcp->psh<<endl;
        cout<<"Reset Flag: "<<tcp->rst<<endl;
        cout<<"Synchronize Flag: "<<tcp->syn<<endl;
        cout<<"Finish Flag: "<<tcp->fin<<endl;
        cout<<"Window: "<<ntohs(tcp->window)<<endl;
        cout<<"Checksum: "<<ntohs(tcp->check)<<endl;
        cout<<"Urgent Pointer: "<<tcp->urg_ptr<<endl;
        cout<<"------------------------------------------------------------"<<endl<<endl;
        cout<<"Payload: "<<buffer+iphdrlen<<endl;
        cout<<"------------------------------------------------------------"<<endl<<endl;
        memset(buffer, 0, sizeof(buffer));
    }
    return 0;

}