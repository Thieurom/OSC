#ifndef __HISTORY_H

#define MAX_LINE (80)
#define MAX_ARGS (MAX_LINE/2 + 1)
#define MAX_SIZE (10)

typedef struct __entry_t {
    char command[MAX_LINE];
    struct __entry_t *next;
} entry_t;

typedef struct __history_t {
    entry_t *top;
    int count;
    int capacity;
} history_t;

entry_t *create_entry(void);
history_t *create_history(void);
void push_history(history_t *history, entry_t *entry);
entry_t *history_entry(history_t *history, int n);
void print_history(history_t *history);

#endif  /* __HISTORY_H */
