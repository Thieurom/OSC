#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "shell.h"


static int shell_parse(char *command, char **args)
{
    char *delim;
    int argc;
    int bg;

    /* Replacing trailing '\n' with space */
    command[strlen(command) - 1] = ' ';

    /* Ignore leading spaces */
    while (*command && (*command == ' '))
        command++;

    /* Build the args list */
    argc = 0;
    while ((delim = strchr(command, ' '))) {
        args[argc++] = command;
        /* Terminate current argument */
        *delim = '\0';

        /* Point to next argument */
        command = delim + 1;
        /* Ignore spaces */
        while (*command && (*command == ' '))
            command++;
    }

    args[argc] = NULL;

    /* Ignore blank line */
    if (argc == 0)
        return 1;

    /* Check whether or not run commnad in background */
    if ((bg = (*args[argc-1] == '&')) != 0)
        args[--argc] = NULL;

    return bg;
}

static int shell_builtin_command(history_t *history, char **args)
{
    if (!strcmp(args[0], "history")) {
        print_history(history);
        return 1;
    }

    if (!strcmp(args[0], "!!")) {
        if (history->count) {
            printf("%s", (history->top)->command);
            shell_eval(history->top->command, history);
        } else {
            printf("No commands in history.\n");
        }

        return 1;
    }

    if (!strcmp(args[0], "!")) {
        int n = atoi(args[1]);
        entry_t *e;

        if ((e = history_entry(history, n)) == NULL) {
            printf("No such command in history.\n");
        } else {
            printf("%s", e->command);
            shell_eval(e->command, history);
        }

        return 1;
    }

    return 0;
}

void shell_read(char *command, int n)
{
    fgets(command, n, stdin);
}

void shell_eval(char *command, history_t *history)
{
    pid_t pid;
    int bg;
    char *args[MAX_ARGS];
    char buffer[MAX_LINE];

    strcpy(buffer, command);
    bg = shell_parse(buffer, args);

    if (args[0] == NULL)
        return;

    if (!shell_builtin_command(history, args)) {
        /* Store command as the new, top entry of the history */
        entry_t *e = create_entry();
        strcpy(e->command, command);
        e->next = NULL;
        push_history(history, e);

        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork failed.\n");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            /* Child process runs the command */
            if (execvp(args[0], args) < 0) {
                printf("%s: command not found.\n", args[0]);
                exit(EXIT_SUCCESS);
            }
        }

        if (!bg) {
            wait(0);
        } else {
            printf("%d %s", pid, args[0]);
        }
    }
}
