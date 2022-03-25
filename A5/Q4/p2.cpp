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

const char *sem1="S1";
const char *sem2="S2";

int main()
{
    sem_t *S1 = sem_open(sem1, O_EXCL);
    sem_t *S2 = sem_open(sem2, O_EXCL);

    if(S1 == SEM_FAILED || S2 == SEM_FAILED)
	{
		perror("Semaphore Creation failure!");    
        sem_unlink(sem1);
        sem_unlink(sem2);
        exit(1);
	}
    key_t key1 = ftok("green",32);
    key_t key2 = ftok("red",32);

    int shmid1 = shmget(key1,100,0666 | IPC_CREAT);
    int shmid2 = shmget(key2,100,0666 | IPC_CREAT);
    if(shmid1 == -1 || shmid2 == -1)
    {
        perror("Shared memory creation failed!");
        shmctl(shmid1,IPC_RMID,NULL);
        shmctl(shmid2,IPC_RMID,NULL);
        exit(1);
    }
    int *x = (int *)shmat(shmid1, 0, 0);
    int *y = (int *)shmat(shmid2, 0, 0);
    

    cout<<"I am waiting for S1"<<endl;
    sem_wait(S1);

    cout<<"Original Value X: "<< *x <<endl;
    cout<<"Original Value Y: "<< *y <<endl;
    
    *y = *x + 1;
    cout<<"Enter any character to signal S2 ";
    char c; cin>>c;
    sem_post(S2);
    cout<<"New Value X: "<< *x <<endl;
    cout<<"New Value Y: "<< *y <<endl;
    shmdt(x); shmdt(y);
    sem_unlink(sem1);
    sem_unlink(sem2);
}