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
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;
#define PORT 4040

int main()
{
    cout<<"In Client 3."<<endl;
    // socket client
    int sfd, valread;
    struct sockaddr_in address;
    char buffer[100] = {0};

    // socket file descriptor
    // getting a socket
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    cout << "Socket created" << endl;

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0)
    {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    cout << "Connecting to the server ..." << endl;
    // connect the client socket to server socket
    while (connect(sfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("connect");
        cout << "Connection failed, retrying...." << endl;
    }
    cout << "Connection established...\n";

    while (1)
    {
        string s;
        cout << "Enter text to capitalize: ";
        getline(cin, s);
        strcpy(buffer, s.c_str());
        send(sfd, buffer, s.size(), 0);
        memset(buffer, 0, 1024);
        valread = read(sfd, buffer, 1024);
        string msg(buffer);
        cout << msg << endl;
        memset(buffer, 0, 1024);
    }

    close(sfd);

    return 0;
}