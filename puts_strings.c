#include "shell.h"

/**
 * copy_string - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *copy_string(char *destination, char *source)
{
    int i = 0;

    if (destination == source || source == 0)
        return (destination);
    while (source[i])
    {
        destination[i] = source[i];
        i++;
    }
    destination[i] = 0;
    return (destination);
}

/**
 * duplicate_string - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *duplicate_string(const char *str)
{
    int length = 0;
    char *result;

    if (str == NULL)
        return (NULL);
    while (*str++)
        length++;
    result = malloc(sizeof(char) * (length + 1));
    if (!result)
        return (NULL);
    for (length++; length--;)
        result[length] = *--str;
    return (result);
}

/**
 * print_string - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void print_string(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        print_character(str[i]);
        i++;
    }
}

/**
 * print_character - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_character(char c)
{
    static int index;
    static char buffer[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
    {
        write(1, buffer, index);
        index = 0;
    }
    if (c != BUFFER_FLUSH)
        buffer[index++] = c;
    return (1);
}
