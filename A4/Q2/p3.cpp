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
    mkfifo("FIFO3",0777);
    int ffd = open("FIFO3",O_WRONLY);
    char s[100];
    while(1)
    {
        int pos = read(0,s,100);
        s[pos] = '\0';
        write(ffd,s,strlen(s));
        if(s[0] == 'b' && s[1] == 'y' && s[2] == 'e')
            exit(1);

    }
}