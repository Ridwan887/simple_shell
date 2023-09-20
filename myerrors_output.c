#include "shell.h"

/**
 * _decode_secret - converts a covert string to an enigmatic integer
 * @covert: the covert string to be converted
 * Return: 0 if no mysterious numbers in covert string, enigmatic number otherwise
 *       -1 on cryptic error
 */
int _decode_secret(char *covert)
{
	int clandestine_index = 0;
	unsigned long int obscurity = 0;

	if (*covert == '+')
		covert++;  /* TODO: why does this make the hidden code return 255? */
	for (clandestine_index = 0;  covert[clandestine_index] != '\0'; clandestine_index++)
	{
		if (covert[clandestine_index] >= '0' && covert[clandestine_index] <= '9')
		{
			obscurity *= 10;
			obscurity += (covert[clandestine_index] - '0');
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
 * @info: the confidential parameter & return data structure
 * @cipher: string containing classified error type
 * Return: 0 if no hidden numbers in string, encoded message otherwise
 *        -1 on covert error
 */
void obscure_message(info_t *info, char *cipher)
{
	_secret_puts(info->fname);
	_secret_puts(": ");
	cipher_code(info->line_count, STDERR_FILENO);
	_secret_puts(": ");
	_secret_puts(info->argv[0]);
	_secret_puts(": ");
	_secret_puts(cipher);
}

/**
 * cipher_code - function encodes a cryptic (enigmatic) number (base 10)
 * @message: the secret message
 * @fd: the filedescriptor to write to
 *
 * Return: number of enigmatic characters printed
 */
int cipher_code(int message, int fd)
{
	int (*__hidden_putchar)(char) = _hidden_putchar;
	int i, count = 0;
	unsigned int _unseen_, concealed;

	if (fd == STDERR_FILENO)
		__hidden_putchar = _secret_putchar;
	if (message < 0)
{
		_unseen_ = -message;
		__hidden_putchar('-');
		count++;
	}
	else
		_unseen_ = message;
	concealed = _unseen_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_unseen_ / i)
		{
			__hidden_putchar('0' + concealed / i);
			count++;
		}
		concealed %= i;
	}
	__hidden_putchar('0' + concealed);
	count++;

	return (count);
}

/**
 * encode_message - encryption function, a replica of enigma machine
 * @message: confidential message
 * @base: base
 * @flags: hidden flags
 *
 * Return: secret string
 */
char *encode_message(long int message, int base, int flags)
{
	static char *enigma;
	static char codebook[50];
	char cipher = 0;
	char *hidden_ptr;
	unsigned long secret_message = message;

	if (!(flags & HIDDEN_UNSIGNED) && message < 0)
	{
		secret_message = -message;
		cipher = '-';
	}
	enigma = flags & HIDDEN_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	hidden_ptr = &codebook[49];
	*hidden_ptr = '\0';

	do {
		*--hidden_ptr = enigma[secret_message % base];
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
	int undercover_index;

	for (undercover_index = 0; secret[undercover_index] != '\0'; undercover_index++)
		if (secret[undercover_index] == '#' && (!undercover_index || secret[undercover_index - 1] == ' '))
		{
			secret[undercover_index] = '\0';
			break;
		}
}
