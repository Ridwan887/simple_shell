#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/** Define environ if not available */
extern char **environ;

#define MAX_INPUT_SIZE 1024
#define MAX_ALIAS_COUNT 100

/** Define a structure to hold alias information */
struct Alias
{
	char *name;
	char *value;
};

// Declare an array to store aliases
struct Alias aliases[MAX_ALIAS_COUNT];
int alias_count;

// Function prototypes

/**
 * print_aliases - Print all stored aliases.
 * Description: Prints all aliases stored in the 'aliases' array.
 */
void print_aliases(void);

/**
 * find_alias - Find an alias by name.
 * @name: The name of the alias to find.
 *
 * Return: A pointer to the alias structure, or NULL if not found.
 * Description: Searches for an alias with the given name in the 'aliases' array.
 */
struct Alias *find_alias(char *name);

/**
 * execute_command - Execute a single shell command.
 * @command: The command to execute.
 * Description: Executes a single shell command in a child process.
 */
void execute_command(char *command);

/**
 * read_user_input - Read user input from stdin.
 * @input: The input string buffer.
 * @input_length: The length of the input string buffer.
 *
 * Return: 1 if successful, 0 on Ctrl+D (end of file), or -1 on error.
 * Description: Reads user input from stdin and stores it in the 'input' buffer.
 */
int read_user_input(char *input, size_t input_length);

/**
 * print_aliases - Print all stored aliases.
 * Description: Prints all aliases stored in the 'aliases' array.
 * Return: 0 if successful, -1 on error
 */
void print_aliases(void)
{
	int i;
	for (i = 0; i < alias_count; i++)
	{
		printf("%s='%s'\n", aliases[i].name, aliases[i].value);
	}
}

/**
 * find_alias - Find an alias by name.
 * @name: The name of the alias to find.
 *
 * Return: A pointer to the alias structure, or NULL if not found.
 * Description: Searches for an alias with the given name in the 'aliases' array.
 */
struct Alias *find_alias(char *name)
{
	int i;
	for (i = 0; i < alias_count; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			return (NULL);
		}
	}
	return (NULL);
}

/**
 * execute_command - Execute a single shell command.
 * @command: The command to execute.
 * Description: Executes a single shell command in a child process.
 */
void execute_command(char *command)
{
	char *args[MAX_INPUT_SIZE];
	char *token;
	int arg_count = 0;
	pid_t pid = fork();
	char *path;
	char *path_copy;
	int command_found = 0;

	token = strtok(command, " ");
	while (token != NULL)
	{
		args[arg_count] = token;
		arg_count++;
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;
	if (arg_count == 1 && strcmp(args[0], "exit") == 0)
	{
		printf("Exiting the shell\n");
		exit(EXIT_SUCCESS);
	}

	if (arg_count == 1 && strcmp(args[0], "env") == 0)
	{
		char **env = environ;
		while (*env != NULL)
		{
			printf("%s\n", *env);
			env++;
		}
		return; /** Skip fork and prompt */
	}

	path = getenv("PATH");
	path_copy = strdup(path);
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		char command_path[1024];
		snprintf(command_path, sizeof(command_path), "%s/%s", token, args[0]);
		if (access(command_path, X_OK) == 0)
		{
			command_found = 1;
			break;
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);

	if (!command_found)
	{
		printf("Command not found: %s\n", args[0]);
		return; // Skip fork if command doesn't exist
	}

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		int status;
		if (wait(&status) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			printf("Command execution failed\n");
		}
	}
}

/**
 * read_user_input - Read user input from stdin.
 * @input: The input string buffer.
 * @input_length: The length of the input string buffer.
 *
 * Return: 1 if successful, 0 on Ctrl+D (end of file), or -1 on error.
 * Description: Reads user input from stdin and stores it in the 'input' buffer.
 */
int read_user_input(char *input, size_t input_length)
{
	if (fgets(input, input_length, stdin) == NULL)
	{
		return (0);
	}

	size_t input_len = strlen(input);
	if (input_len > 0 && input[input_len - 1] == '\n')
	{
		input[input_len - 1] = '\0';
	}

	return (1); // Successful input
}

/**
 * main - Reads main functions
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];
	size_t input_length;

	while (1)
	{
		printf("shell$ "); // Display the prompt
		if (read_user_input(input, sizeof(input)) == 0)
		{
			printf("\n");
			break;
		}
	}
	return 0;
}

