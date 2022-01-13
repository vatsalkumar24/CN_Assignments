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
    mkfifo("green", 0777);
    //int ffd = open("green",O_WRONLY);
    while(1)
    {
        char buff[100];
        int ffd = open("green",O_WRONLY);
        read(0,buff,100);
        if(buff[0] == '\0')
        {
            break;
        }
        cout<<endl<<"msg: "<<buff<<endl;
        int n = strlen(buff);
        for(int i=0; i<n; i++)
        {
            if(buff[i]>='a' && buff[i]<='z')
                buff[i] = buff[i] - 32;
        }
        char temp[] = " from P3\n";
        strcat(buff,temp);
        write(ffd,buff,strlen(buff)+1);
    }
}