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
#include <semaphore.h>
#include <bits/stdc++.h>
using namespace std;
const char *sem34 = "S34";
const char *sem41 = "S41";
int main()
{
    sem_t *S34 = sem_open(sem34, O_EXCL);
    sem_t *S41 = sem_open(sem41, O_EXCL);
    if(S34 == SEM_FAILED || S41 == SEM_FAILED)
    {
        perror("Semaphore Creation failure!");  
        sem_unlink(sem34);
        sem_unlink(sem41);
        exit(1);
    }
    char ch;
    cout<<"I am P4.I am waiting for semaphore S34"<<endl;
    if(sem_wait(S34) == -1)
    {
        perror("Semaphore wait failure!");  
        exit(1);
    }
    cout<<"I got semaphore S34 signalling from P3"<<endl;
    cout<<"Enter any character to sem-signal(S41)\n";
    cin>>ch;
    cout<<"I am signalling semaphore signal of S41"<<endl;
    if(sem_post(S41) == -1)
    {
        perror("Semaphore send failure!");  
        exit(1);
    }   

}