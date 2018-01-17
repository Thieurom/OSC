/**
 * Programming Problem 5.37
 * ========================
 * Resource manager
 */


#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_RESOURCES 5

int available_resources = MAX_RESOURCES;
sem_t empty;
sem_t lock;

int increase_count(int count);
int decrease_count(int count);
void *runner(void *param);

int main()
{
    pthread_t clients[5];
    pthread_attr_t attr;
    int i;

    sem_init(&lock, 0, 1);
    sem_init(&empty, 0, MAX_RESOURCES);
    pthread_attr_init(&attr);

    printf("available resources: %d\n", available_resources);

    for (i = 0; i < 5; i++)
        pthread_create(&clients[i], &attr, runner, (void *) (i + 1));

    for (i = 0; i < 5; i++)
        pthread_join(clients[i], NULL);

    return 0;
}

int decrease_count(int count)
{
    sem_wait(&empty);
    sem_wait(&lock);
    if (available_resources < count) {
        return -1;
    } else {
        available_resources -= count;
        printf("decreased %d -> available: %d\n", count, available_resources);
        sem_post(&lock);
        return 0;
    }
}

int increase_count(int count)
{
    sem_wait(&lock);
    available_resources += count;
    printf("increased %d -> available: %d\n", count, available_resources);
    sem_post(&lock);
    sem_post(&empty);

    return 0;
}

void *runner(void *param)
{
    int count = (int) param;
    while (decrease_count(count) == -1)
        ;
    sleep(count);
    increase_count(count);

    pthread_exit(0);
}
