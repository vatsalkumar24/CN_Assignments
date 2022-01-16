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
int returned_pid;
void get_pid(int sig, siginfo_t *info, void *context)
{
    returned_pid = info->si_pid;
}
int main()
{
    int pid = getpid(), prevpid, nextpid;
    cout<<"P1(pid): "<<pid<<endl;
    key_t key = 1234;
    int msqid = msgget(key,0666|IPC_CREAT);
    if(msqid == -1) 
    {
        perror("message queue creation failed!");
        exit(1);
    }
    struct mymsg msg;
    if(msgrcv(msqid,&msg, sizeof(msg), 2, 0) == -1)
    {
        perror("msgrcv failed!");
        exit(1);
    }
    else {
        nextpid = get_int(msg.mdata, strlen(msg.mdata));
        cout<<"Next pid: "<<nextpid<<endl;
        if(kill(nextpid,SIGUSR1) == 0)
            cout<<"P1 send SIGUSR1 to P"<<msg.mtype<<endl;
    }
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = get_pid;
    sigaction(SIGUSR1,&sa,NULL);
    prevpid = returned_pid;
    cout<<"Previous ID: "<<prevpid<<endl;
}
