/**
 * Programming Problem 5.36
 * =======================================================
 * Thread safe multithreaded program work with pid manager
 */


#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define N_THREADS 100
#define MAX_SLEEP 15

#define MIN_PID   300
#define MAX_PID   5000

pthread_mutex_t mutex;
void *runner(void *param);
int map[MAX_PID - MIN_PID + 1];
int allocate_map(void);
int allocate_pid(void);
void release_pid(int pid);

int main()
{
    pthread_t workers[N_THREADS];
    pthread_attr_t attr;
    int i;

    pthread_attr_init(&attr);
    pthread_mutex_init(&mutex, NULL);
    allocate_map();

    for (i = 0; i < N_THREADS; i++) {
        pthread_create(&workers[i], &attr, runner, NULL);
    }

    for (i = 0; i < N_THREADS; i++) {
        pthread_join(workers[i], NULL);
    }

    return EXIT_SUCCESS;
}

void *runner(void *param)
{
    int pid = allocate_pid();
    int runtime = rand() % (MAX_SLEEP + 1);

    printf("new thread: %d\n", pid);
    sleep(runtime);
    release_pid(pid);
    pthread_exit(0);
}

int allocate_map(void)
{
    int size = MAX_PID - MIN_PID;

    for (int i = 0; i <= size; i++)
        map[i] = 0;

    return 1;
}

int allocate_pid(void)
{
    int size = MAX_PID - MIN_PID;

    pthread_mutex_lock(&mutex);
    for (int i = 0; i <= size; i++) {
        if (map[i] == 0) {
            map[i] = 1;
            pthread_mutex_unlock(&mutex);

            return i + MIN_PID;
        }
    }

    return 1;
}

void release_pid(int pid)
{
    if (pid >= MIN_PID && pid <= MAX_PID)
        map[pid - MIN_PID] = 0;
}
