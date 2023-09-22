#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

// Function declarations
int simple_shell_01(void);
int simple_shell_02(void);

/* shell_buffer.c */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
int main(int argc, char *argv[]);

#endif /* SHELL_H */

