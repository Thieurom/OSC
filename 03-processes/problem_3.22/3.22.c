/**
 * Programming Problem 3.22
 * ===========================
 * IPC by shared memory object
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int n;
    pid_t pid;
    const int SIZE = 4096;
    const char *name = "collatz";
    int shm_fd;
    void *ptr;

    /* Check user input */
    if (argc != 2) {
        fprintf(stderr, "Require one positive parameter.\n");
        exit(EXIT_FAILURE);
    }

    if ((n = atoi(argv[1])) <= 0) {
        fprintf(stderr, "Require one positive parameter.\n");
        exit(EXIT_FAILURE);
    }

    /* Fork new child */
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed.\n");
        exit(EXIT_FAILURE);
    }

    /* Child process */
    if (pid == 0) {
        /* create and write to shared memory segment */
        shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
        ftruncate(shm_fd, SIZE);
        ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

        while (n > 1) {
            sprintf(ptr, "%d,", n);
            ptr += (int) log10(n) + 2;
            n = (n % 2 == 0) ? (n / 2) : (3 * n + 1);
        }
        sprintf(ptr, "%d", n);
        ptr += (int) log10(n) + 1;

        exit(EXIT_SUCCESS);
    }

    /* Parent process */
    wait(NULL);

    /* open and read from shared memory segment */
    shm_fd = shm_open(name, O_RDONLY, 0666);
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    printf("%s", ptr);

    shm_unlink(name);

    return EXIT_SUCCESS;
}
