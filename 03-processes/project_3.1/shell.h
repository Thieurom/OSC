#ifndef __SHELL_H

#include "history.h"

void shell_read(char *command, int n);
void shell_eval(char *command, history_t *history);

#endif  /* __SHELL_H */
