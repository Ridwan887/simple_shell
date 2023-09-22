#include "shell.h"

/**
 * communicative - Returns true if the shell is in communicative mode.
 * @data: Pointer to a data_d structure.
 *
 * Return: 1 if in communicative mode, 0 otherwise.
 */
int communicative(data_d *data)
{
    return (isatty(STDIN_FILENO) && data->readfd == 2);
}

/**
 * is_delimiterChars - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delimiterChars: A string containing delimiter characters.
 * 
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimiterChars(char c, char *delimiterChars)
{
    while (*delimiterChars) {
        if (*delimiterChars == c) {
            return 1;
        }
        delimiterChars++;
    }
    return 0;
}

/**
 * is_alpha - Checks if a character is alphabetic.
 * @c: The character to check.
 * 
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int is_alpha(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * a_prompt - Converts a string to an integer.
 * @s: The string to convert.
 * 
 * Return: The converted integer, or 0 if no numbers in the string.
 */
int a_prompt(char *s)
{
    int g, sign = 1, flag = 0, output = 0;

    for (g = 0; s[g] != '\0' && flag != 2; g++)
    {
        if (s[g] == '-')
        {
            sign *= -1;
        }
        else if (s[g] >= '0' && s[g] <= '9')
        {
            flag = 1;
            output *= 10;
            output += (s[g] - '0');
        }
        else if (flag == 1)
        {
            flag = 2;
        }
    }

    return (sign * output);
}
