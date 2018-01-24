#include <stdlib.h>
#include <stdio.h>
#include "history.h"


entry_t *create_entry(void)
{
    entry_t *e;

    if ((e = malloc(sizeof(entry_t))) == NULL) {
        exit(EXIT_FAILURE);
    }

    return e;
}

history_t *create_history(void)
{
    history_t *h;

    if ((h = malloc(sizeof(history_t))) == NULL) {
        exit(EXIT_FAILURE);
    }

    h->capacity = MAX_SIZE;
    h->top = NULL;
    h->count = 0;

    return h;
}

void push_history(history_t *history, entry_t *entry)
{
    entry->next = history->top;
    history->top = entry;

    if (history->count < history->capacity) {
        history->count++;
    } else {
        int i = 1;
        entry_t *e = history->top;

        while (i <= history->capacity) {
            e = e->next;
            i++;
        }
        free(e);
    }
}

entry_t *history_entry(history_t *history, int n)
{
    if (n < 1 || n > history->count) {
        return NULL;
    } else {
        int count = history->count;
        entry_t *e = history->top;

        while (n < count) {
            e = e->next;
            count--;
        }

        return e;
    }
}

void print_history(history_t *history)
{
    entry_t *e = history->top;

    for (int i = history->count; i >= 1; i--) {
        printf("%d %s", i, e->command);
        e = e->next;
    }
}
