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
int prevpid, nextpid;
int fwdcnt = 3, revcnt = 3;
void prev_handler(int sig, siginfo_t *info, void *context)
{
    prevpid = info->si_pid;
    cout<<"previous process pid: "<<prevpid<<endl;
}
void next_handler()
{
    cout<<"next process pid: "<<nextpid<<endl;
}
void fwdsignaling(int signo)
{
    fwdcnt--;
    if(fwdcnt == -1) return;
    kill(nextpid,SIGUSR1);
    cout<<"P1->P2"<<endl;
}
void revsignaling(int signo)
{
    revcnt--;
    if(revcnt == -1) return;
    kill(prevpid,SIGUSR2);
    cout<<"P1->P4"<<endl;
}
int main()
{
    int pid = getpid();
    cout<<"P1(pid): "<<pid<<endl;
    key_t key = ftok("green",32);
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
        nextpid = stoi(string(msg.mdata));
        next_handler();
        if(kill(nextpid,SIGUSR1) == 0)
            cout<<"P1 sent SIGUSR1 to P2 succcessfully"<<endl;
    }
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = prev_handler;
    sigaction(SIGUSR1,&sa,NULL);
    pause();
    
    kill(nextpid,SIGUSR1);
    signal(SIGUSR1, fwdsignaling);
    while(fwdcnt) pause();

    signal(SIGUSR2, revsignaling);
    kill(prevpid,SIGUSR2);
    while(revcnt) pause();

}
