#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
int main()
{
    FILE* fd = popen("./p3","w");
    dup2(fileno(fd),1);
    while(1)
    {
        char s[100];
        read(0,s,100);
        write(1,s,strlen(s)+1);
        if(s[0] == '\0') break;
    }
}