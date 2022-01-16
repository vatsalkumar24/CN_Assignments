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
    cout<<"P4->P1"<<endl;
}
void revsignaling(int signo)
{
    revcnt--;
    if(revcnt == -1) return;
    kill(prevpid,SIGUSR2);
    cout<<"P4->P3"<<endl;
}
int main()
{
    int pid = getpid();
    cout<<"P4(pid): "<<pid<<endl;
    key_t key = ftok("green",32);
    int msqid = msgget(key,0666|IPC_CREAT);
    if(msqid == -1) 
    {
        perror("message queue creation failed!");
        exit(1);
    }
    struct mymsg msg;
    msg.mtype = 4;
    string s = to_string(pid);
    strcpy(msg.mdata,s.c_str());
    msgsnd(msqid,&msg,sizeof(msg), 0);
    //cout<<"P4 message sent to msqid"<<endl; 
     
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = prev_handler;
    sigaction(SIGUSR1,&sa,NULL);
    pause();

    memset(msg.mdata, 0, 100);
    if(msgrcv(msqid,&msg, sizeof(msg), 1, 0) == -1)
    {
        perror("msgrcv failed!");
        exit(1);
    }
    else {
        nextpid = stoi(string(msg.mdata));
        next_handler();
        if(kill(nextpid,SIGUSR1) == 0)
            cout<<"P4 sent SIGUSR1 to P1 succcessfully"<<endl;
    }


    signal(SIGUSR1, fwdsignaling);
    while(fwdcnt) pause();

    signal(SIGUSR2, revsignaling);
    while(revcnt) pause();

}
