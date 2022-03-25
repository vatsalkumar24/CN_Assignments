#include <unistd.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <bits/stdc++.h>
#include <arpa/inet.h>
using namespace std;
int main()
{
    int itfd = open("abc.txt", O_RDWR);
    int outfd = open("123.txt", O_RDWR);
    dup2(itfd,0); dup2(outfd,1);
      
    
    return 0;
}