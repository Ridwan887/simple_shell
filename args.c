#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

int simple_shell_02(void) {
    char input[MAX_INPUT_SIZE];
    size_t input_length;
    pid_t pid;

    while (1) {
        char *args[MAX_INPUT_SIZE];  // Declare args array here
        char *token;                 // Declare token here
        int arg_count = 0;           // Reset arg_count
        
        printf("shell$ ");  // Display the prompt
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle Ctrl+D (end of file)
            printf("\n");
            break;
        }

        // Remove the trailing newline character
        input_length = strlen(input);
        if (input_length > 0 && input[input_length - 1] == '\n') {
            input[input_length - 1] = '\0';
        }

        // Tokenize the input to separate command and arguments
        token = strtok(input, " ");
        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;  // Null-terminate the argument list

        // Fork a new process
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            if (wait(&status) == -1) {
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}

