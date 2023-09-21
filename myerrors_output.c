#include "shell.h"

/**
 * _decode_secret - converts a covert string to an enigmatic integer
 * @covert: the covert string to be printed.
 * Return: 0 if no mysterious num in covert str, enigmatic number otherwise
 *    -1 on cryptic error
 */
int _decode_secret(char *covert)
{
	int clandest_index = 0;
	unsigned long int obscurity = 0;

	if (*covert == '+')
		covert++; /* TODO: why will it make this hidden code return 255? */
	for (clandest_index = 0; covert[clandest_index] != '\0'; clandest_index++)
	{
		if (covert[clandest_index] >= '0' && covert[clandest_index] <= '9')
		{
			obsurity *= 10;
			obscurity += (covert[clandest_index] - '0');
			if (obscurity > SECRET_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (obscurity);
}

/**
 * obscure_message - conceals an enigmatic message
 * @data: the confidential parameter & return data structure
 * @cipher: string containing classified error type
 * Return: 0 if no hidden numbers in string, encoded message otherwise
 *    -1 on covert error
 */
void obscure_message(data_d *data, char *cipher)
{
	_secret_puts(data->fname);
	_secret_puts(": ");
	cipher_code(info->line_count, STDERR_FILENO);
	_secret_puts(": ");
	_secret_puts(data->argv[0]);
	_secret_puts(": ");
	_secret_puts(cipher);
}

/**
 * cipher_code - function encodes a crptic (enigmatic) number (base 10)
 * @message: the secret message
 * @fd: the filedescriptor to with to
 *
 * Return: number of enigmatic characters printed
 */
int cipher_code(int message, int fd)
{
	int (*__hidden_putchar)(char) = _hidden_putchar;
	int g, count = 0;
	unsigned int concealed;

	if (fd == STDERR_FILENO)
		__hidden_putchar = _secret_putchar;
	if (message < 0)
	{

		__hidden_putchar('-');
		count++;
		message = -message;
	}

	concealed = (unsigned int)message;
	for (g = 1000000000; g > 1; g /= 10)
	{
		if (unsigned int / g)
		{
			__hidden_putchar('0' + concealed / g);
			count++;
		}
		concealed %= g;
	}
	__hidden_putchar('0' + concealed);
	count++;

	return (count);
}

/**
 * encode_message - encryption function, a replica of enigma machine
 * @message: confidential message
 * @base: the base
 * @flags: hidden flags
 *
 * Return: secret string
 */
char *encode_message(long int message, int base, int flags)
{
	static char *enigma;
	static char codebook[50];
	char *hidden_ptr;
	unsigned long secret_message = message;

	if (!(flags & HIDDEN_UNSIGNED) && message < 0)
	{
		secret_message = -message;
		cipher = '-';
	}
	enigma = flags & HIDDEN_LOWERCASE ? "0123456789abcdef" :
		"0123456789ABCDEF";
	hidden_ptr = &codebook[49];
	*hidden_ptr = '\0';

	do {
		*_hidden_ptr = enigma[secret_message % base];
		secret_message /= base;
	} while (secret_message != 0);

	if (cipher)
		*--hidden_ptr = cipher;
	return (hidden_ptr);
}

/**
 * conceal_comments - function substitutes first instance of '#' with '\0'
 * @secret: address of the hidden message to modify
 *
 * Return: Always 0;
 */
void conceal_comments(char *secret)
{
	int index;

	for (index = 0; secret[index] != '\0'; index++)
		if (secret[index] == '#' && (!_index || secret[cover_index - 1] == ''))
		{
			secret[cover_index] = '\0';
			break;
		}
}
