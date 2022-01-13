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
long get_int(string s)
{
	long num = 0;
	for(int i=0; i<s.length(); i++)
	{
		int temp = s[i] - '0';
		num = num*10 + temp;
	}
	cout<<num<<endl;
	return num;
}
int main()
{
	map<long,string >mp; 
	key_t key = 1234;
	int msqid=msgget(key,0666|IPC_CREAT);
	struct mymsg msg;
	int i=0;
	while(i<3)
	{
		if(msgrcv(msqid, &msg, sizeof(msg),0,0) == -1)
		{
			perror("msgrcv failure!");
			break;
		}
		cout<<"Recieving from msqid"<<endl;
		if(mp.find(msg.mtype)!=mp.end())
		    cout<<mp[msg.mtype]<<" : "<<msg.mdata<<endl;
		else
		{
			mp[msg.mtype]=msg.mdata;
		}
		cout<<msg.mtype<<" : "<<mp[msg.mtype]<<endl;
		i++;
	}

	cout<<"exited"<<endl;
	struct mymsg p1;
	p1.mtype = get_int(mp[2]);
	strcpy(p1.mdata ,"message from P1 to P2\n");
	msgsnd(msqid,&p1,sizeof(p1),0);
	cout<<"Writing to msqid"<<endl;

	struct mymsg p2;
	p2.mtype = get_int(mp[3]);
	strcpy(p2.mdata ,"message from P1 to P3\n");
	msgsnd(msqid,&p2,sizeof(p2),0);
	cout<<"Writing to msqid"<<endl;

	struct mymsg p3 ;
	p3.mtype = get_int(mp[4]);
	strcpy(p3.mdata ,"message from P1 to P4\n");
	msgsnd(msqid,&p3,sizeof(p3),0);
	cout<<"Writing to msqid"<<endl;

	msgctl(msqid, IPC_RMID, NULL);
}