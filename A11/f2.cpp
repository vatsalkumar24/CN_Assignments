// raw sockets need "sudo ./s" to run
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
#include <netinet/tcp.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <bits/stdc++.h>
using namespace std;
#define PORT 8080
#define MAXLINE 4096
void print_content(unsigned char *buf, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        if (i != 0 && i % 16 == 0)
        {
            printf("          ");
            for (size_t j = (i - 16); j < i; j++)
            {
                if (buf[j] >= 32 && buf[j] <= 128)
                { // print "printable" characters
                  // printf("%c", (char)((unsigned char)buf[j]));
                }
                else
                {
                    // printf("."); // Otherwise add a dot
                }
            }
            printf("\n");
        }

        if (i % 16 == 0)
            printf("    ");
        cout << buf[i];

        if (i == (length - 1))
        {
            for (size_t j = 0; j < (15 - 1 % 16); j++)
                printf("    ");
            printf("          ");

            for (size_t j = (i - i % 16); j <= 1; j++)
            {
                if (buf[j] >= 32 && buf[j] <= 128)
                {
                }
                // printf("%c", (char)((unsigned char)buf[j]));
                else
                {
                }
                // printf(".");
            }
            printf("\n");
        }
    }
}
int main()
{
    int sfd;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    if ((sfd = socket(AF_INET, SOCK_RAW, 2)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sfd, (const struct sockaddr*)&addr, sizeof(addr));

    struct sockaddr_in clientAddr;
    int len = sizeof(clientAddr);
    memset(&clientAddr, 0, sizeof(clientAddr));

    cout<<"Fielder 2 on position"<<endl;
    unsigned char buffer[MAXLINE];
    int packetSize = recvfrom(sfd, (char*)buffer, MAXLINE,0, (sockaddr*)&clientAddr,(socklen_t*)&len);

    cout<<"Run scored : ";
    unsigned char tempBuff[MAXLINE];
    for (int i = 0; i < MAXLINE; i++)
        tempBuff[i] = buffer[i];
    struct iphdr *iph = (struct iphdr *)buffer;
    unsigned short ip_head_len = iph->ihl * 4;
    struct tcphdr *tcp_head = (struct tcphdr *)(tempBuff + ip_head_len);
    print_content(tempBuff + ip_head_len + tcp_head->th_off * 4, (packetSize - tcp_head->th_off * 4 - iph->ihl * 4));
    
    close(sfd);
    return 0;
}