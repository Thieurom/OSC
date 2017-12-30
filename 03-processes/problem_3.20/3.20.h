/**
 * Programming Problem 3.20
 * ===================================
 * Implement a very simple pid manager
 */


#ifndef __PID_MANAGER_H
#define __PID_MANAGER_H

#define MIN_PID  300
#define MAX_PID  5000

int allocate_map(void);
int allocate_pid(void);
void release_pid(int pid);

#endif  /* __PID_MANAGER_H */
