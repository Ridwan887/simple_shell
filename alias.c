#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Define environ if not available
extern char **environ;

#define MAX_INPUT_SIZE 1024
#define MAX_ALIAS_COUNT 100

// Define a structure to hold alias information
struct Alias {
    char *name;
    char *value;
};

// Declare an array to store aliases
struct Alias aliases[MAX_ALIAS_COUNT];
int alias_count = 0;

// Function to print all aliases
void print_aliases(void);

// Function to find an alias by name
struct Alias *find_alias(char *name);

// Function to execute a single command
void execute_command(char *command);

int _main_(void) {
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

// Function to print all aliases
void print_aliases(void) {
    int i;
    for (i = 0; i < alias_count; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

// Function to find an alias by name
struct Alias *find_alias(char *name) {
    int i;
    for (i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            return &aliases[i];
        }
    }
    return NULL;
}

// Function to execute a single command
void execute_alias(char *command) {
    char *args[MAX_INPUT_SIZE];
    char *token;
    int arg_count = 0;
    pid_t pid = fork();
    char *path;
    char *path_copy;
    int command_found = 0;

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

    // Check if the command exists in one of the directories listed in PATH
    path = getenv("PATH");
    path_copy = strdup(path);
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
        return; // Skip fork if command doesn't exist
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
