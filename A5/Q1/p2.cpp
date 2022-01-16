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
	char mdata[100];	
};
long get_int(char s[], int n)
{
	long num = 0;
	for(int i=0; i<n; i++)
	{
		int temp = s[i] - '0';
		num = num*10 + temp;
	}
	cout<<num<<endl;
	return num;
}
int returned_pid = -1;
void get_pid(int sig, siginfo_t *info, void *context)
{
    returned_pid = info->si_pid;
}
int main()
{
    
    int pid = getpid(), prevpid, nextpid;
    cout<<"P2(pid): "<<pid<<endl;
    key_t key = 1234; 
    int msqid = msgget(key,0666|IPC_CREAT);
    
    if(msqid == -1) 
    {
        perror("message queue creation failed!");
        exit(1);
    }
    struct mymsg msg;
    msg.mtype = 2;
    string s = to_string(pid);
    for(int i=0; i<s.length(); i++)
        msg.mdata[i] = s[i];
    msgsnd(msqid,&msg,sizeof(msg), 0);
    cout<<"P2 message sent to msqid"<<endl;
    

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = get_pid;
    cout<<sigaction(SIGUSR1,&sa,NULL)<<endl;
    prevpid = returned_pid;
    cout<<"Previous ID: "<<prevpid<<endl;

    if(msgrcv(msqid,&msg, sizeof(msg), 3, 0) == -1)
    {
        perror("msgrcv failed!");
        
    }
    else {
        nextpid = get_int(msg.mdata, strlen(msg.mdata));
        cout<<"Next pid: "<<nextpid<<endl;
    }
    
    msg.mtype = 1;
    s = to_string(prevpid);
    for(int i=0; i<s.length(); i++)
        msg.mdata[i] = s[i];
    msgsnd(msqid,&msg,sizeof(msg), 0);
    cout<<"P2 message sent to msqid"<<endl;

    if(kill(nextpid,SIGUSR1) == 0)
        cout<<"P2 send SIGUSR1 to P3"<<endl;
    msgctl(msqid, IPC_RMID, NULL);
    
}