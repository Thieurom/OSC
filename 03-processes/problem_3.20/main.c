/**
 * Programming Problem 3.20
 * ===================================
 * Implement a very simple pid manager
 */


#include <stdio.h>
#include "3.20.h"

int main()
{
    int pid1, pid2;

    allocate_map();

    pid1 = allocate_pid();
    printf("pid: %d\n", pid1);

    pid2 = allocate_pid();
    printf("pid: %d\n", pid2);

    release_pid(pid1);

    pid1 = allocate_pid();
    printf("pid: %d\n", pid1);

    return 0;
}
