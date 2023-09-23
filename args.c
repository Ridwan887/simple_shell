#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/**
 * print_prompt - Display the shell prompt.
 */
void print_prompt(void)
{
	printf("shell$ ");
}

/**
 * read_user_input - Read user input from stdin.
 * @input: The input string buffer.
 * @input_length: The length of the input string buffer.
 *
 * Return: 1 if successful, 0 on Ctrl+D (end of file), or -1 on error.
 */
int read_user_input(char *input, size_t input_length)
{
	if (fgets(input, input_length, stdin) == NULL)
	{
		printf("\n");
		return (0);
	}

	size_t input_len = strlen(input);

	if (input_len > 0 && input[input_len - 1] == '\n')
	{
		input[input_len - 1] = '\0';
	}

	return (1);
}

/**
 * tokenize_input - Tokenize user input into arguments.
 * @input: The input string to tokenize.
 * @args: An array to store the resulting arguments.
 *
 * Return: The number of arguments parsed.
 */
int tokenize_input(char *input, char *args[])
{
	char *token = strtok(input, " ");
	int arg_count = 0;

	while (token != NULL)
	{
		args[arg_count] = token;
		arg_count++;
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;

	return (arg_count);
}

/**
 * execute_command - Execute a single shell command.
 * @args: The command and its arguments to execute.
 *
 * Return: 0 on success, -1 on failure.
 */
int execute_command(char *args[])
{
	pid_t pid = fork();

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
			return (-1);  /** Command execution failed */
		}
	}

	return (0);
}

/**
 * simple_shell_02 - Reads user input
 * tokenizes it into arguments and execute in child process
 * Return: 0 on success, or an error code on failure.
 */
int simple_shell_02(void)
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		print_prompt();

		if (read_user_input(input, sizeof(input)) == 0)
			break;
		char *args[MAX_INPUT_SIZE];
		int arg_count = tokenize_input(input, args);

		if (arg_count == 0)
			continue;  /** Empty input, skip to the next iteration */

		if (strcmp(args[0], "exit") == 0)
		{
			int exit_status = 0;

			if (arg_count > 1)
			{
				exit_status = strtol(args[1], NULL, 10);

				if (errno == EINVAL || errno == ERANGE)
				{
					printf("Invalid exit status: %s\n", args[1]);
					errno = 0;
					continue;
				}
			}
			printf("Exiting the shell with status: %d\n", exit_status);
			exit(exit_status);
		}

		if (execute_command(args) == -1)
		{
			printf("Command not found: %s\n", args[0]);
		}
	}

	return (0);
}
