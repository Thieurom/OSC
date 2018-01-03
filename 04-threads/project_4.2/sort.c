/*
 * Programming Project 4.2
 * Multithreaded Sorting Application
 */


#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 10

typedef struct {
    int left;
    int right;
} list;

list *new_list(int left, int right);
void *sort(void *param);
void *merge(void *param);


/****************************************************************************/


int original_list[SIZE] = { 7, 12, 19, 3, 18, 4, 2, 6, 15, 8 };
int sorted_list[SIZE];

int main()
{
    int i;
    list *left_list, *right_list, *merged_list;
    pthread_t sort_workers[2], merge_worker;
    pthread_attr_t attr;

    /* print the original list */
    for (i = 0; i < SIZE; i++)
        printf("%d ", original_list[i]);

    printf("\n");

    /* get the default attributes */
    pthread_attr_init(&attr);

    /* create thread for sorting the left-half of the original list */
    left_list = new_list(0, SIZE/2 - 1);
    pthread_create(&sort_workers[0], &attr, sort, left_list);

    /* create thread for sorting the right-half of the original list */
    right_list = new_list(SIZE/2, SIZE - 1);
    pthread_create(&sort_workers[1], &attr, sort, right_list);

    /* wait for sorting */
    for (i = 0; i < 2; i++)
        pthread_join(sort_workers[i], NULL);

    /* create thread for merging two sorted halves into one */
    merged_list = new_list(0, SIZE - 1);
    pthread_create(&merge_worker, &attr, merge, merged_list);

    /* wait for merging */
    pthread_join(merge_worker, NULL);

    /* print the sortde list */
    for (i = 0; i < SIZE; i++)
        printf("%d ", sorted_list[i]);

    printf("\n");

    return EXIT_SUCCESS;
}

/*
 * Sort the list, use insertion sort algorithm
 */
void *sort(void *param)
{
    int i, j, left, right, temp;
    list *list_param = (list *) param;

    left = list_param->left;
    right = list_param->right;

    for (i = left + 1; i <= right; i++) {
        j = i;

        while (j > left && original_list[j] < original_list[j-1]) {
            temp = original_list[j];
            original_list[j] = original_list[j-1];
            original_list[j-1] = temp;
            j--;
        }
    }

    pthread_exit(0);
}

/*
 * Merge two sorted list into one.
 */
void *merge(void *param)
{
    int i, j, k, left, middle, right;
    list *list_param = (list *) param;

    left = list_param->left;
    right = list_param->right;
    middle = (left + right) / 2;

    i = left;
    j = middle + 1;
    k = 0;
    while (i <= middle && j <= right) {
        if (original_list[i] < original_list[j])
            sorted_list[k++] = original_list[i++];
        else
            sorted_list[k++] = original_list[j++];
    }

    while (i <= middle)
        sorted_list[k++] = original_list[i++];

    while (j <= right)
        sorted_list[k++] = original_list[j++];

    pthread_exit(0);
}

/*
 * Return pointer to new list with specified left and right bounds.
 */
list *new_list(int left, int right)
{
    list *new_list;

    if ((new_list = (list *) malloc(sizeof(list))) == NULL) {
        fprintf(stderr, "Fail allocated memory.\n");
        exit(EXIT_FAILURE);
    }

    new_list->left = left;
    new_list->right = right;

    return new_list;
}
