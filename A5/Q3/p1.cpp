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
const char *sem12 = "S12";
const char *sem41 = "S41";
int main()
{
    sem_t *S12 = sem_open(sem12, O_CREAT | O_EXCL, 0666, 0);
    sem_t *S41 = sem_open(sem41, O_CREAT | O_EXCL, 0666, 0);
    if(S12 == SEM_FAILED || S41 == SEM_FAILED)
    {
        perror("Semaphore Creation failure!");  
        sem_unlink(sem12);
        sem_unlink(sem41);
        exit(1);
    }
    char ch;
    cout<<"I am P1.Enter any character to sem-signal(S12)"<<endl;
    cin>>ch;
    cout<<"I am signalling semaphore signal of S12"<<endl;
    if(sem_post(S12) == -1)
    {
        perror("Semaphore send failure!");  
        exit(1);
    }
    cout<<"I am waiting for semaphore S41"<<endl;
    if(sem_wait(S41) == -1)
    {
        perror("Semaphore wait failure!");  
        exit(1);
    }
    cout<<"I got semaphore signalling from P4"<<endl;

    sem_unlink(sem12);
    sem_unlink(sem41);
}