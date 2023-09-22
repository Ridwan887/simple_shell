#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT_SIZE 1024

int execute_command(char *command);
int find_command_path(char *command, char *path);

/**
 * read_user_input - Read user input from stdin.
 *
 * @input: The input string buffer.
 * @input_length: The length of the input string.
 *
 * Return: 1 if successful, 0 on Ctrl+D (end of file), or -1 on error.
 */
int read_user_input(char *input, size_t input_length)
{
	printf("shell$ ");
	if (fgets(input, input_length, stdin) == NULL)
	{
		printf("\n");
		return (0); /* Ctrl+D (end of file) */
	}

	size_t input_len = strlen(input);

	if (input_len > 0 && input[input_len - 1] == '\n')
	{
		input[input_len - 1] = '\0';
	}

	return (1); /* Successful input */
}

/**
 * parse_input - Tokenize input into arguments.
 *
 * @input: The input string to tokenize.
 * @args: An array to store the resulting arguments.
 *
 * Return: The number of arguments parsed.
 */
int parse_input(char *input, char *args[])
{
	char *token = strtok(input, " ");
	int arg_count = 0;

	while (token != NULL)
	{
		args[arg_count] = token;
		arg_count++;
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL; /* Null-terminate the argument list */
	return (arg_count);
}

/**
 * simple_shell_041 - A simple shell implementation.
 *
 * This function reads user input, tokenizes it into arguments,
 * and executes the specified command in a child process.
 *
 * Return: 0 on success, or an error code on failure.
 */
int simple_shell_041(void)
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		if (read_user_input(input, sizeof(input)) == 0)
		{
			break;
		}

		char *args[MAX_INPUT_SIZE];
		int arg_count = parse_input(input, args);

		if (arg_count == 0)
			continue; /* Empty input, skip to next iteration */

		if (strcmp(args[0], "exit") == 0)
		{
			/* Handle "exit" command */
			int exit_status = 0;

			if (arg_count > 1)
			{
				exit_status = strtol(args[1], NULL, 10);
				if (errno == EINVAL || errno == ERANGE)
				{
					printf("Invalid exit status: %s\n", args[1]);
					errno = 0; /* Reset errno */
					continue;
				}
			}
			printf("Exiting the shell with status: %d\n", exit_status);
			exit(exit_status);
		}

		/* Execute the specified command */
		if (execute_command(args[0]) == -1)
		{
			printf("Command not found: %s\n", args[0]);
		}
	}

	return (0);
}

/**
 * execute_command - Execute a command in a child process.
 *
 * @command: The command to execute.
 *
 * Return: 0 on success, or -1 on failure.
 */
int execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0);
	{
		/* Child process */
		if (execvp(command, args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		/* Parent process */
		int status;

		if (wait(&status) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			return (-1); /* Command execution failed */
		}
	}

	return (0);
}

/**
 * main - Prints main
 * @void: argument
 * Return: 0 if true success
 */
int main(void)
{
	return (simple_shell_041());
}
