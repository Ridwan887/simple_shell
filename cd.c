#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Declare environ if not available
extern char **environ;

#define MAX_INPUT_SIZE 1024

int cd(void) {
    char input[MAX_INPUT_SIZE];
    size_t input_length;
    char current_directory[MAX_INPUT_SIZE];

    while (1) {
        char *args[MAX_INPUT_SIZE];  // Declare args array here
        char *token;                 // Declare token here
        int arg_count = 0;           // Reset arg_count
        char *path = getenv("PATH");
        char *path_copy = strdup(path);
        int command_found = 0;
        pid_t pid = fork();

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
            continue; // Skip fork and prompt
        }

        // Check if the command is "cd"
        if (arg_count == 1 && strcmp(args[0], "cd") == 0) {
            // Change the current directory to the home directory
            if (chdir(getenv("HOME")) == -1) {
                perror("chdir");
            }
            // Update the PWD environment variable
            if (getcwd(current_directory, sizeof(current_directory)) != NULL) {
                setenv("PWD", current_directory, 1);
            } else {
                perror("getcwd");
            }
            continue; // Skip fork and prompt
        }

        // Check if the command exists in one of the directories listed in PATH
        token = strtok(path_copy, ":");

        while (token != NULL) {
            char command_path[1024];
            snprintf(command_path, sizeof(command_path), "%s/%s", token, args[0]);
            if (access(command_path, X_OK) == 0) {
                command_found = 1;
                break;
            }
            token = strtok(NULL, ":");
        }
        free(path_copy);

        if (!command_found) {
            printf("Command not found: %s\n", args[0]);
            continue; // Skip fork if command doesn't exist
        }

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

    return 0;
}
