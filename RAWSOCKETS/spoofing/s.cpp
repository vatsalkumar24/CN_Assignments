#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <bits/stdc++.h>
#define MAXLINE 4096
using namespace std;
void printIPHeader(struct iphdr *ip)
{
    cout << "IP Header: \n";
    cout << "IP version:" << (unsigned int)ip->version << endl;
    cout << "IP header length:" << (unsigned int)ip->ihl << endl;
    cout << "Type of service:" << (unsigned int)ip->tos << endl;
    cout << "Total ip packet length:" << ntohs(ip->tot_len) << endl;
    cout << "Packet id:" << ntohs(ip->id) << endl;
    cout << "Time to leave :" << (unsigned int)ip->ttl << endl;
    cout << "Protocol:" << (unsigned int)ip->protocol << endl;
    cout << "Check:" << ip->check << endl;
    cout << "Source ip:" << inet_ntoa(*(in_addr *)&ip->saddr) << endl;
    cout << "Destination ip:" << inet_ntoa(*(in_addr *)&ip->daddr) << endl;
}

void printPayload(struct ip *iph, unsigned char *tempBuff, int packetSize)
{
    cout << "Payload: ";
    unsigned short ip_head_len = iph->ip_hl * 4;
    struct tcphdr *tcp_head = (struct tcphdr *)(tempBuff + ip_head_len);
    unsigned char *buf = tempBuff + ip_head_len + tcp_head->th_off * 4;
    size_t length = (packetSize - tcp_head->th_off * 4 - iph->ip_hl * 4);

    for (size_t i = 0; i < length; i++)
    {
        if (i != 0 && i % 16 == 0)
        {
            for (size_t j = (i - 16); j < i; j++)
            {
                if (buf[j] >= 32 && buf[j] <= 128)
                {
                }
            }
            printf("\n");
        }

        cout << buf[i];

        if (i == (length - 1))
        {
            printf("\n");
        }
    }
}

int main()
{
    int s = socket(PF_INET, SOCK_RAW, 1);
    int one = 1;
    const int *val = &one;
    if (setsockopt(s, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0)
    {
        cout << "could not enable HDRINCL...\n";
        exit(1);
    }
    struct sockaddr_in addr, client;
    socklen_t len = sizeof(client);
    char buff[MAXLINE];
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8081);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(s, (struct sockaddr *)&addr, sizeof(addr));
    while (true)
    {
        cout << "Waiting for IP Packet...\n";
        int packetSize = recvfrom(s, buff, MAXLINE, 0, (struct sockaddr *)&client, &len);
        struct iphdr *iph = (struct iphdr *)buff;
        struct ip *ip = (struct ip *)buff;
        unsigned char tempBuff[MAXLINE];
        for (int i = 0; i < MAXLINE; i++)
            tempBuff[i] = buff[i];
        printIPHeader(iph);
        printPayload(ip, tempBuff, packetSize);
        cout << endl;
    }
}