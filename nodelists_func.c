#include "shell.h"

size_t determineListLength(const list_t *node)
{
	size_t length = 0;

	while (node)
	{
		node = node->next;
		length++;
	}
	return (length);
}

char **convertListToStrings(list_t *list)
{
	list_t *node = list;
	size_t count = determineListLength(list);
	char **strings;
	char *str;

	if (!list || !count)
		return (NULL);

	strings = malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (NULL);

	for (count = 0; node; node = node->next, count++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < count; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		_strcpy(str, node->str);
		strings[count] = str;
	}

	strings[count] = NULL;
	return (strings);
}

size_t displayList(const list_t *node)
{
	size_t count = 0;

	while (node)
	{
		_printString(convertToDecimalString(node->num));
		_printChar(':');
		_printChar(' ');
		_printString(node->str ? node->str : "(nil)");
		_printString("\n");
		node = node->next;
		count++;
	}
	return (count);
}

list_t *findNodeWithPrefix(list_t *node, char *prefix, char character)
{
	char *position = NULL;

	while (node)
	{
		position = startsWithPrefix(node->str, prefix);
		if (position && ((character == -1) || (*position == character)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

ssize_t getNodeIndex(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
