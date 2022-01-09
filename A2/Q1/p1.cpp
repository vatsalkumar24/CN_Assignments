#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int main()
{
    int pfd1[2], pfd2[2];
    int x = pipe(pfd1), y = pipe(pfd2);
    if(x == -1){
        cout<<"Pipe1 creation failed!.\n";
        return 0;
    }
    if(y == -1){
        cout<<"Pipe2 creation failed!.\n";
        return 0;
    }
    int c = fork();
    if(c>0)
    {
        close(pfd1[0]);
        close(pfd2[1]);
        while(1)
        {
            char pwmsg[100];
            cout<<"Parent Write msg: ";
            cin>>pwmsg;
            if(pwmsg == "")
            {
                exit(0);
            }
            write(pfd1[1],pwmsg,sizeof(pwmsg)+1);
            char prmsg[100];
            read(pfd2[0],prmsg,sizeof(prmsg));
            cout<<"Parent Read msg: "<<prmsg<<endl;
        }
    }
    else{
        close(pfd1[1]);
        close(pfd2[0]);
        while(1){
            char crmsg[100];
            read(pfd1[0],crmsg,sizeof(crmsg));
            cout<<"Child Read msg: "<<crmsg<<endl;
            char cwmsg[100];
            cout<<"Child Write msg: ";
            cin>>cwmsg;
            if(cwmsg == "\n")
            {
                exit(0);
            }
            write(pfd2[1],cwmsg,sizeof(cwmsg)+1);
        }
    }
    return 0;
}
