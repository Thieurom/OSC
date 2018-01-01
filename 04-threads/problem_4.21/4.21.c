/**
 * Programming Problem 4.21
 * =========================================================
 * Multithreaded program calculates various statiscal values
 * for a list of numbers.
 */


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>

int size, min, max, avg;
void *find_min(void *param);
void *find_max(void *param);
void *find_avg(void *param);

int main(int argc, char *argv[])
{
    pthread_t tmin, tmax, tavg;
    pthread_attr_t attr;
    int numbers[size], i;

    if (argc == 1) {
        fprintf(stderr, "No given arguments. Aborted.\n");
        exit(EXIT_FAILURE);
    }

    size = argc - 1;
    for (i = 0; i < size; i++)
        numbers[i] = atoi(argv[i + 1]);

    pthread_attr_init(&attr);
    pthread_create(&tmin, &attr, find_min, numbers);
    pthread_create(&tmax, &attr, find_max, numbers);
    pthread_create(&tavg, &attr, find_avg, numbers);

    pthread_join(tmin, NULL);
    pthread_join(tmax, NULL);
    pthread_join(tavg, NULL);

    printf("The average value is %d\n", avg);
    printf("The minimum value is %d\n", min);
    printf("The maximum value is %d\n", max);

    return EXIT_SUCCESS;
}

void *find_min(void *param)
{
    int *num = (int *) param;
    min = INT_MAX;

    for (int i = 0; i < size; i++) {
        if (num[i] < min)
            min = num[i];
    }

    pthread_exit(0);
}

void *find_max(void *param)
{
    int *num = (int *) param;
    max = INT_MIN;

    for (int i = 0; i < size; i++) {
        if (num[i] > max)
            max = num[i];
    }

    pthread_exit(0);
}

void *find_avg(void *param)
{
    int sum = 0;
    int *num = (int *) param;

    for (int i = 0; i < size; i++) {
        sum += num[i];
    }

    avg = sum / size;

    pthread_exit(0);
}
