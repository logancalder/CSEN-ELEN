// Name : Logan Calder
// Date: 10/30/2024
// Title: Lab5 – Part 4
// Description: This file contains a thread synchronization program that uses condition variables to synchronize threads.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define NUMPRODUCER 3
#define NUMCONSUMER 2
#define n 10

pthread_t tidP[NUMPRODUCER], tidC[NUMCONSUMER];
int buff[n];
pthread_mutex_t lock;
pthread_cond_t full, empty;

int p, c, in, out;
int count = 0;

void *producer(void *arg)
{
    do
    {
        int thing;
        thing = rand() % 100;

        while (count == n)
        {
            pthread_cond_wait(&empty, &lock);
        }

        buff[in] = thing;
        in = (in + 1) % n;
        count++;

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&lock);
        printf("produced: %d\n", thing);
    } while (1);
}

void *consumer(void *arg)
{
    do
    {
        pthread_mutex_lock(&lock);
        while (count == 0)
        {
            pthread_cond_wait(&full, &lock);
        }
        int thing = buff[out];
        out = (out + 1) % n;
        count--;

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&lock);

        printf("\tconsumed: %d\n", thing);
    } while (1);
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);
    for (p = 0; p < NUMPRODUCER; ++p)
    {
        pthread_create(&tidP[p], NULL, producer, (void *)(size_t)p);
    }
    for (c = 0; c < NUMCONSUMER; c++)
    {
        pthread_create(&tidC[c], NULL, consumer, (void *)(size_t)c);
    }
    for (p = 0; p < NUMPRODUCER; p++)
    {
        pthread_join(tidP[p], NULL);
        printf("producer %d returned\n", p);
    }
    for (c = 0; c < NUMCONSUMER; c++)
    {
        pthread_join(tidC[c], NULL);
        printf("consumer %d returned\n", c);
    }
    printf("finished\n");
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);
    return 0;
}