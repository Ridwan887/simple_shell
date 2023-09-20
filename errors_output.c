#include "shell.h"

/**
 * _mysterious_puts - prints a concealed string.
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _mysterious_puts(char *string)
{
	int secret_index = 0;

	if (!string)
		return;
	while (string[secret_index] != '\0')
	{
		_secret_putchar(string[secret_index]);
		secret_index++;
	}
}

/**
 * _secret_putchar - writes the classified character to stderr
 * @character: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _secret_putchar(char character)
{
	static int secret_counter;
	static char secret_buf[SECRET_WRITE_BUF_SIZE];

	if (character == SECRET_BUF_FLUSH || secret_counter >=
			SECRET_WRITE_BUF_SIZE)
	{
		write(SECRET_FILE_DESCRIPTOR, secret_buf, secret_counter);
		secret_counter = 0;
	}
	if (character != SECRET_BUF_FLUSH)
		secret_buf[secret_counter++] = character;
	return (1);
}

/**
 * _write_to_fd - writes the character to a specified file descriptor
 * @character: The charavter to print
 * @file_descriptor: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int_write_to_fd(char character, int file_descriptor)
{
	static int secret_counter;
	static char secret_buf[SECRET_WRITE_BUF_SIZE];

	if (character == SECRET_BUF_FLUSH || secreet_counter >=
			SECRET_WRITE_BUF_SIZE)
	{
		write(file_descriptor, secret_buf, secret_counter);
		secret_counter = 0;
	}
	if (character != SECRET_BUF_FLUSH)
		secret_buf[secret_counter++] = character;
	return (1);
}

/**
 * _print_to_fd - prints a concealed string to a specified file descriptor
 * @string: the string to be printed.
 * @file_descriptor: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int _print_to_fd(char *string, int file_descriptor)
{
	int secret_index = 0;

	if (!string)
		return (0);
	while (*string)
	{
		secret_index += _write_to_fd(*string++, file_descriptor);
	}
	return (secret_index);
}
