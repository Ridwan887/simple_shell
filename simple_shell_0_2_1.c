#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/**
 * tokenizeInput - Tokenize an input string into arguments.
 * @input: The input string to tokenize.
 * @args: An array to store the resulting arguments.
 * @arg_count: A pointer to an integer to store the number of arguments.
 */
void tokenizeInput(char *input, char *args[], int *arg_count)
{
	char *token = NULL;
	int i = 0;

	while ((token = strtok(input, " ")) != NULL)
	{
		args[i] = token;
		i++;
		input = NULL;
	}
	args[i] = NULL;  /* Null-terminate the argument list */
	*arg_count = (i);
}

/**
 * simple_shell_0_2_1 - Reads simple shell function implementation.
 * This function reads user input, tokenizes it into arguments,
 * and executes the specified command in a child process.
 * Return: 0 on success, or an error code on failure.
 */
int simple_shell_0_2_1(void)
{
	char input[MAX_INPUT_SIZE];
	size_t input_length;
	pid_t pid;

	while (1)
	{
		char *args[MAX_INPUT_SIZE];
		int arg_count = 0;

		printf("shell$ ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input_length = strlen(input);
		if (input_length > 0 && input[input_length - 1] == '\n')
		{
			input[input_length - 1] = '\0';
		}
		tokenizeInput(input, args, &arg_count);
		pid = fork();
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
		}
	}
	return (0);
}
