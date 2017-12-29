/**
 * Programming Problem 3.19
 */


#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(EXIT_FAILURE);
    }
    
    /* Child process */
    if (pid == 0) {
        exit(EXIT_SUCCESS);
    }

    /* Parent process */
    sleep(10);  /* Give time to observe the zombie */

    return EXIT_SUCCESS;
}
