/**
 * Programming Problem 3.21
 * ========================
 * Collatz conjecture
 */


#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int n;
    pid_t pid;

    if (argc != 2) {
        fprintf(stderr, "Require one positive parameter.\n");
        exit(EXIT_FAILURE);
    }

    if ((n = atoi(argv[1])) <= 0) {
        fprintf(stderr, "Require one positive parameter.\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(EXIT_FAILURE);
    }

    /* Child process */
    if (pid == 0) {
        while (n > 1) {
            printf("%d,", n);
            n = (n % 2 == 0) ? (n / 2) : (3 * n + 1);
        }
        printf("%d\n", n);
    }

    /* Parent process */
    wait(NULL);

    return EXIT_SUCCESS;
}
