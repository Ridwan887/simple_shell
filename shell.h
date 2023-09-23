#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/** Function declarations */
int simple_shell_01(void);
int simple_shell_02(void);

/* Function prototypes */
int execute_command(char *command);
int find_command_path(char *command, char *path);

/* shell_buffer.c */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
int main(int argc, char *argv[]);

/* simple_shell_0_2_1.c */
void tokenizeInput(char *input, char *args[], int *arg_count);
int simple_shell_0_2_1(void);

/* simple_shell_0_4_1.c */
int read_user_input(char *input, size_t input_length);
int parse_input(char *input, char *args[]);
int simple_shell_041(void);
int execute_command(char *command);
int main(void);

/* alias.c */
void print_aliases(void);
struct Alias *find_alias(char *name);
void execute_command(char *command);
int read_user_input(char *input, size_t input_length);
int main(void);

/* args.c */
void print_prompt(void);
int read_user_input(char *input, size_t input_length);
int tokenize_input(char *input, char *args[]);
int execute_command(char *args[]);
int simple_shell_02(void);

#endif /* SHELL_H */

