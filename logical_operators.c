#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Declare environ if not available
extern char **environ;

#define MAX_INPUT_SIZE 1024

// Function to execute a single command
void execute_operators(char *command) {
    char *args[MAX_INPUT_SIZE];
    char *token;
    int arg_count = 0;
    pid_t pid = fork();
    int status;

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        // Tokenize the command to separate command and arguments
        token = strtok(command, " ");
        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;  // Null-terminate the argument list

        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        // Exit child process on successful execution
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        if (wait(&status) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            printf("Command execution failed\n");
        }
    }
}

int logical_operators(void) {
    char input[MAX_INPUT_SIZE];
    size_t input_length;

    while (1) {
        char *token;
        int status;

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

        token = strtok(input, ";"); // Split input by semicolon
        while (token != NULL) {
            if (strstr(token, "&&")) {
                // Handle && operator
                char *command1 = strtok(token, "&&");
                char *command2 = strtok(NULL, "&&");
                execute_operators(command1);
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                    execute_operators(command2);
                }
            } else if (strstr(token, "||")) {
                // Handle || operator
                char *command1 = strtok(token, "||");
                char *command2 = strtok(NULL, "||");
                execute_operators(command1);
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                    execute_operators(command2);
                }
            } else {
                // Single command without operators
                execute_operators(token);
            }
            token = strtok(NULL, ";"); // Get next command
        }
    }

    return 0;
}
