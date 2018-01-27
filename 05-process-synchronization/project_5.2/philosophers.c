/**
 * Programming Project 5.2
 * ===============================
 * The Dining Philosophers Problem
 */


#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


/*
 * Assume philosophers and forks identified by a number 0...4, both follow clockwise direction.
 * The ith philosopher has the ith fork on his/her left-hand side.
 */

int forks[5];
pthread_mutex_t mutex;
pthread_cond_t cond;
void *make_activities(void *param);
void pickup_forks(int philosopher_number);
void return_forks(int philosopher_number);

int main()
{
    pthread_t philosophers[5];
    int i;

    // Init mutex and conditional variable
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // Create threads
    for (i = 0; i < 5; i++) {
        pthread_create(&philosophers[i], NULL, make_activities, (void *) (uintptr_t) i);
    }

    // Wait for threads to exit
    for (i = 0; i < 5; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}


void *make_activities(void *param)
{
    int p = (int) param;

    sleep(rand() % 4);  // Thinking time
    pickup_forks(p);

    printf("Philosopher %d is eating.\n", p);
    sleep(rand() % 4);  // Eating time

    return_forks(p);
    printf("Philosopher %d finished eating.\n", p);
    pthread_exit(0);
}

void pickup_forks(int p)
{
    pthread_mutex_lock(&mutex);

    // Try to pick up the forks
    while (forks[p] && forks[(p+4)%5]) {
        pthread_cond_wait(&cond, &mutex);
    }

    // Can pick up 2 adjuscent forks
    forks[p] = 1;
    forks[(p+4)%5] = 1;

    pthread_mutex_unlock(&mutex);
}

void return_forks(int p)
{
    pthread_mutex_lock(&mutex);

    // Return forks
    forks[p] = 0;
    forks[(p+4)%5] = 0;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}
