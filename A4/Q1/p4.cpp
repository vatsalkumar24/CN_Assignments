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
using namespace std;
struct mymsg
{
	long mtype;
	char mdata[2048];	
};
int main()
{
	struct mymsg message[10];
	key_t key = 1234;
	int msqid;
	if((msqid = msgget(key,0666|IPC_CREAT)) == -1)
	{
		perror("Message queue creation failed");
		exit(1);
	}
	struct mymsg msg;
	msg.mtype=4;
    int pid4 = getpid();
    string s = to_string(pid4);
    for(int i=0; i<s.length(); i++)
        msg.mdata[i] = s[i];
	cout<<"Writing to msqid"<<endl;
	msgsnd(msqid,&msg,sizeof(msg), 0);
	
	struct mymsg rcv;
	if(msgrcv(msqid,&rcv,sizeof(rcv),pid4,0) == -1)
	{
		perror("msgrcv failure!.");
	}
	else cout<<rcv.mdata<<endl;	
}