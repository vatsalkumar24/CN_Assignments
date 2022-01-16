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
const char *sem23 = "S23";
const char *sem34 = "S34";
int main()
{
    sem_t *S23 = sem_open(sem23, O_EXCL);
    sem_t *S34 = sem_open(sem34, O_CREAT | O_EXCL, 0666, 0);
    if(S23 == SEM_FAILED || S34 == SEM_FAILED)
    {
        perror("Semaphore Creation failure!");  
        sem_unlink(sem23);
        sem_unlink(sem34);
        exit(1);
    }
    char ch;
    cout<<"I am P3.I am waiting for semaphore S23"<<endl;
    if(sem_wait(S23) == -1)
    {
        perror("Semaphore wait failure!");  
        exit(1);
    }
    cout<<"I got semaphore S23 signalling from P2"<<endl;
    cout<<"Enter any character to sem-signal(S34)\n";
    cin>>ch;
    cout<<"I am signalling semaphore signal of S34"<<endl;
    if(sem_post(S34) == -1)
    {
        perror("Semaphore send failure!");  
        exit(1);
    }   

    sem_unlink(sem34);
}