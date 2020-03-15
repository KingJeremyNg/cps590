/*
2) The thread and the main problem are running concurrently while accessing the same myglobal and assigning it out of sync.
3) Each loop of the thread and main problem will have to run one at a time for myglobal variable to be incremented correctly.
*/

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>

/*
Purpose: Use 2 threads to increment myglobal exactly 40 times in total.
Compile: using -pthread option
*/

int myglobal = 0;
sem_t sem;

void *thread_function(void *arg)
{
    int i, j;

    for (i = 0; i < 20; i++)
    {
        sem_wait(&sem);
        j = myglobal;
        j = j + 1;
        myglobal = j;
        sem_post(&sem);
        printf(".");
        fflush(stdout);
        sleep(0.2);
    }
    sem_destroy(&sem);

    return NULL;
}

int main(void)
{
    pthread_t mythread;
    int i;
    sem_init(&sem, 0, 1);

    if (pthread_create(&mythread, NULL, thread_function, NULL))
    {
        printf("error creating thread.");
        abort();
    }

    for (i = 0; i < 20; i++)
    {
        sem_wait(&sem);
        myglobal = myglobal + 1;
        sem_post(&sem);
        printf("o");
        fflush(stdout);
        sleep(0.21);
    }

    if (pthread_join(mythread, NULL))
    {
        printf("error joining thread.");
        abort();
    }

    printf("\nmyglobal equals %d\n", myglobal);

    exit(0);
}
