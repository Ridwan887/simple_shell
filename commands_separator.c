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
void execute_command(char *command) {
    char *args[MAX_INPUT_SIZE];
    char *token;
    int arg_count = 0;
    pid_t pid = fork();

    // Tokenize the command to separate command and arguments
    token = strtok(command, " ");
    while (token != NULL) {
        args[arg_count] = token;
        arg_count++;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;  // Null-terminate the argument list

    // Check if the command is "exit"
    if (arg_count == 1 && strcmp(args[0], "exit") == 0) {
        printf("Exiting the shell\n");
        exit(EXIT_SUCCESS);
    }

    // Check if the command is "env"
    if (arg_count == 1 && strcmp(args[0], "env") == 0) {
        // Print the environment variables
        char **env = environ;
        while (*env != NULL) {
            printf("%s\n", *env);
            env++;
        }
        return; // Skip fork and prompt
    }

    // Execute the command
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        // Exit child process on successful execution
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        int status;
        if (wait(&status) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            printf("Command execution failed\n");
        }
    }
}

int command_separator(void) {
    char input[MAX_INPUT_SIZE];
    size_t input_length;
    char *command;

    while (1) {
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

        // Tokenize the input to separate commands based on semicolon
        command = strtok(input, ";");
        while (command != NULL) {
            execute_command(command);
            command = strtok(NULL, ";");
        }
    }

    return 0;
}

