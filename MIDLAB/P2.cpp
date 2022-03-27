#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <poll.h>
#include <unistd.h>
using namespace std;

int main()
{
    cout<<"In P2"<<endl;
    char buffer[100];
    mkfifo("fifo2", 0777);
    int fd = open("fifo2", O_RDWR);
    while(1)
    {
        cout<<"Enter text: ";
        cin.getline(buffer,100);
        if(buffer[0] == '\0')
            break;
        write(fd, buffer, sizeof(buffer) + 1);
    }
    close(fd);
    return 0;
}