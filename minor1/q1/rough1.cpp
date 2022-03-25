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
#include <unordered_map>
using namespace std;
struct msg{
    long type;
    char text[100];
};
struct service{
    int s_sfd1;
    int s_sfd2;
};
map<int,service> cnt;
void signal_handler1(int sig, siginfo_t *info, void *context)
{
    int pid = info->si_pid;
    if(cnt.find(pid) == cnt.end())
    {
        cnt[pid].s_sfd1=1;
    }else{
        cnt[pid].s_sfd1++;
    }
    cout<<"PID  SF1  SF2"<<endl;
    for(auto itr: cnt)
    {
        cout<<itr.first<<" "<<itr.second.s_sfd1<<"  "<<itr.second.s_sfd2<<endl;
    }
}
void signal_handler2(int sig, siginfo_t *siginfo, void *context)
{
    int pid = siginfo->si_pid;
    if(cnt.find(pid) == cnt.end())
    {
        cnt[pid].s_sfd2++;
    }
    cout<<"PID  SF1  SF2"<<endl;
    for(auto itr: cnt)
    {
        cout<<itr.first<<" "<<itr.second.s_sfd1<<"  "<<itr.second.s_sfd2<<endl;
    }

}
int main()
{
    int key = ftok("msgq", 65);
    int msqid = msgget(key, 0666 | IPC_CREAT);

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler1;
    
    if(sigaction(SIGUSR1,&sa,NULL)<0) perror("sigaction:");

    sa.sa_sigaction = signal_handler2;
    sa.sa_flags = SA_SIGINFO;
    if(sigaction(SIGUSR2,&sa,NULL)<0) perror("sigaction: ");

    int pid=getpid();
    string s=to_string(pid);
    struct msg message;
    memset(message.text,'\0',100);
    message.type = 1;
    strcpy(message.text,s.c_str());
    msgsnd(msqid, &message, sizeof(message), 0);
    msgsnd(msqid, &message, sizeof(message), 0);
    cout<<"pid sent to queue: "<<message.text<<endl;

    while(1)
    {

    }
}