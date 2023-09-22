#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define MAX_LINE_SIZE 1024

static char input_buffer[MAX_LINE_SIZE];
static size_t buffer_position;
static size_t buffer_size;

/**
 * custom_getline - prints the custom getline function
 * @lineptr: pointer to the buffer where line is stored
 * @n: pointer to size of line buffer
 * @stream: stream line read from
 *
 * Return: The number of bytes read, or -1 on error or end of file.
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t bytesRead = 0;
	ssize_t totalBytesRead = 0;

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (buffer_size == 0)
	{
		buffer_size = read(fileno(stream), input_buffer, sizeof(input_buffer));
		if (buffer_size == (size_t)-1)
		{
			return (-1);
		}
		buffer_position = 0;
	}
	while (buffer_position < buffer_size)
	{
		char current_char = input_buffer[buffer_position++];
		(*n)++;
		if (current_char == '\n')
		{
			(*lineptr)[bytesRead++] = '\0';
			return (totalBytesRead + bytesRead - 1);
		}
		if ((size_t)bytesRead >= *n)
		{
			*n *= 2;
			*lineptr = realloc(*lineptr, *n);
			if (*lineptr == NULL)
			{
				return (-1);
			}
		}
		(*lineptr)[bytesRead++] = current_char;
		totalBytesRead++;
	}
	buffer_size = 0;
	return (-1);
}

/**
 * main - Entry point of the program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 *
 * Return: 0 on success, other values on failure
 */
int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t len = 0;

	while (1)
	{
		ssize_t bytesRead = custom_getline(&line, &len, stdin);

		if (bytesRead == -1)
		{
			/** Error or line too long */
			printf("Error reading line.\n");
			break;
		} else if (bytesRead == 0)
		{
			printf("\n");
			break;
		}
		else
		{
			/** Successfully read a line*/
			printf("Read %zd bytes: %s\n", bytesRead, line);
		}
	}

	free(line);
	return (0);
}

