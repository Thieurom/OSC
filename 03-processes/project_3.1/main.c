#include <stdio.h>
#include "shell.h"


int main()
{
    char command[MAX_LINE];
    history_t *history = create_history();
    int should_run = 1;

    while (should_run) {
        printf("osh> ");
        fflush(stdout);

        shell_read(command, MAX_LINE);
        shell_eval(command, history);
    }

    return 0;
}
