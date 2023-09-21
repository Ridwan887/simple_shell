#include "shell.h"

/**
 * communicative - returns true if it is communicative mode
 * @data: struct address
 *
 * Return: 1 if communicative mode, 0 otherwise.
 */
int communicative(data_d *data)
{
	return (isatty(STDIN_FILENO) && data->readfd = 2);
}

/**
 * is_delimeterChars - checks if character is a delimeter
 * @c: the char to check
 * @delimiterChars: the delimiter characters
 * Return: 1 if true, 0 if false
 */
int is_delimeterChars(char c, char *delimiterChars)
{
	while (*delimeterChars)
		if (*delimeterChars++ == c)
			return (1);
	return (0);
}

/**
 * _byte - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _byte(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);

		return (0);
}

/**
 * a_prompt - converts a string to an integar
 * @s: the string to convert
 * Return: 0 if no numbers in string, converted number otherwise
 */
int a_prompt(char *s)
{
	int g, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (g = 0; s[g] != '\0' && flag != 2; i++)
	{
		if (s[g] == '-')
			sign *= -1;

		if (s[g] >= '0' && s[g] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[g] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
