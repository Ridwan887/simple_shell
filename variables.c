#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Declare environ if not available
extern char **environ;

#define MAX_INPUT_SIZE 1024

// Function to replace variables in a string
char *replace_variables(char *command) {
    char *result = malloc(MAX_INPUT_SIZE); // Allocate memory for the result
    char *cursor = command; // Cursor to traverse the input
    char *output_cursor = result; // Cursor to write to the result
    int last_char_was_dollar = 0;
    int status = 0;
    
    while (*cursor) {
        // Check for $$
        if (last_char_was_dollar && *cursor == '$') {
            snprintf(output_cursor, 10, "%d", getpid()); // Replace $$ with the process ID
            output_cursor += strlen(output_cursor);
            cursor++;
        }
        // Check for $?
        else if (last_char_was_dollar && *cursor == '?') {
            // Replace $? with the exit status of the last command
            snprintf(output_cursor, 10, "%d", WEXITSTATUS(status));
            output_cursor += strlen(output_cursor);
            cursor++;
        }
        // Regular characters
        else {
            *output_cursor++ = *cursor++;
        }

        // Track if the last character was a dollar sign
        last_char_was_dollar = (*cursor == '$');
    }

    *output_cursor = '\0'; // Null-terminate the result
    return result;
}

int simple_shell_2(void) {
    char input[MAX_INPUT_SIZE];
    size_t input_length;
    int status = 0; // To track the exit status of the last command

    while (1) {
        char *args[MAX_INPUT_SIZE];  // Declare args array here
        char *token;                 // Declare token here
        int arg_count = 0;           // Reset arg_count
        char *path = getenv("PATH");
        char *path_copy = strdup(path);
        int command_found = 0;
        pid_t pid = fork();
        char *replaced_input;

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

        // Replace variables ($$ and $?)
        replaced_input = replace_variables(input);

        // Tokenize the input to separate command and arguments
        token = strtok(replaced_input, " ");
        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;  // Null-terminate the argument list

        // Check if the command is "exit"
        if (arg_count == 1 && strcmp(args[0], "exit") == 0) {
            printf("Exiting the shell\n");
            free(replaced_input);
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
            free(replaced_input);
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
            free(replaced_input);
            continue; // Skip fork if command doesn't exist
        }

        if (pid == -1) {
            perror("fork");
            free(replaced_input);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                perror("execvp");
                free(replaced_input);
                exit(EXIT_FAILURE);
            }
            // Exit child process on successful execution
            free(replaced_input);
            exit(EXIT_SUCCESS);
        } else {
            // Parent process
            if (wait(&status) == -1) {
                perror("wait");
                free(replaced_input);
                exit(EXIT_FAILURE);
            }
            free(replaced_input);
        }
    }

    return 0;
}
