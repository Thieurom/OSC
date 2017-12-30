/**
 * Programming Problem 3.20
 * ===================================
 * Implement a very simple pid manager
 */


#include <stdlib.h>
#include "3.20.h"

static int map[MAX_PID - MIN_PID + 1];

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

    for (int i = 0; i <= size; i++) {
        if (map[i] == 0) {
            map[i] = 1;
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
