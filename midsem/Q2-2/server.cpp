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
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <poll.h>
#define PORT1 4040
#define PORT2 5050
using namespace std;

int main()
{
    struct sockaddr_in address1;
    int addrlen = sizeof(address1);
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == 0)
    {
        perror("socket creation failure!");
        exit(EXIT_FAILURE);
    }
    cout << "socket created!" << endl;

    address1.sin_family = AF_INET;
    address1.sin_addr.s_addr = INADDR_ANY;
    address1.sin_port = htons(PORT1);
    if (bind(sfd, (struct sockaddr *)&address1, sizeof(address1)) < 0)
    {
        perror("binding failure");
        exit(EXIT_FAILURE);
    }
    

    struct sockaddr_in address2;
    int asfd;
    if ((asfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket creation failure!");
        exit(EXIT_FAILURE);
    }
    cout << "socket created!" << endl;
    address2.sin_family = AF_INET;
    address2.sin_port = htons(PORT2);
    if (inet_pton(AF_INET, "127.0.0.1", &address2.sin_addr) <= 0)
    {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }
    // connect the client socket to server socket
    if (connect(sfd, (struct sockaddr *)&address2, sizeof(address2)) < 0)
    {
        perror("connect failure");

    }
    printf("Connection established with ip: %s, port:%d\n", ip.c_str(), PORT);
    return sfd;
}