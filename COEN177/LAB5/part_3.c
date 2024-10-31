// Name : Logan Calder
// Date: 10/30/2024
// Title: Lab5 – Part 3
// Description: This file contains a thread synchronization program that uses semaphores to synchronize threads.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define BUFF 10
pthread_t threads[BUFF];
int in;
int out;
int buffer[BUFF];

sem_t *lock;
sem_t *empty;
sem_t *full;

void *consumer(void *arg)
{
    do
    {
        sem_wait(full);
        sem_wait(lock);
        int thing = buffer[out];
        out = (out + 1) % BUFF;
        sem_post(lock);
        sem_post(empty);
        printf("\tConsumed: %d\n", thing);
    } while (1);
}

void *producer(void *arg)
{
    do
    {
        int thing = rand() % 100;
        sem_wait(empty);
        sem_wait(lock);
        buffer[in] = thing;
        in = (in + 1) % BUFF;
        sem_post(lock);
        sem_post(full);
        printf("Produced: %d\n", thing);
        // sleep(1);
    } while (1);
}

int main()
{
    int i;
    sem_unlink("lock2");
    sem_unlink("full2");
    sem_unlink("empty2");

    lock = sem_open("Lock12", O_CREAT, 0644, 1);
    empty = sem_open("Empty21", O_CREAT, 0644, BUFF);
    full = sem_open("Full12", O_CREAT, 0644, 0);

    in = out = 0;
    for (i = 0; i < BUFF / 2; ++i)
    {
        pthread_create(&threads[i], NULL, producer, (void *)(size_t)i);
    }
    for (i = BUFF / 2; i < BUFF; ++i)
    {
        pthread_create(&threads[i], NULL, consumer, (void *)(size_t)i);
    }
    for (i = 0; i < BUFF; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    sem_unlink("lock12");
    sem_unlink("full12");
    sem_unlink("empty21");
    return 0;
}