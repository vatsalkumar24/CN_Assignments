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
const char *sem23 = "S23";
int main()
{
    sem_t *S12 = sem_open(sem12, O_EXCL);
    sem_t *S23 = sem_open(sem23, O_CREAT | O_EXCL, 0666, 0);
    if(S12 == SEM_FAILED || S23 == SEM_FAILED)
    {
        perror("Semaphore Creation failure!");  
        sem_unlink(sem12);
        sem_unlink(sem23);
        exit(1);
    }
    char ch;
    cout<<"I am P2.I am waiting for semaphore S12"<<endl;
    if(sem_wait(S12) == -1)
    {
        perror("Semaphore wait failure!");  
        exit(1);
    }
    cout<<"I got semaphore S12 signalling from P1"<<endl;
    cout<<"Enter any character to sem-signal(S23)\n";
    cin>>ch;
    cout<<"I am signalling semaphore signal of S23"<<endl;
    if(sem_post(S23) == -1)
    {
        perror("Semaphore send failure!");  
        exit(1);
    }   

    sem_unlink(sem23);
}