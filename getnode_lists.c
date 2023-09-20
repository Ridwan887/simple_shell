#include "shell.h"

list_t *prependToList(list_t **start, const char *text, int index)
{
	list_t *newStart;

	if (!start)
		return (NULL);
	newStart = malloc(sizeof(list_t));
	if (!newStart)
		return (NULL);
	_initializeNode(newStart, index);
	if (text)
	{
		_setNodeString(newStart, text);
		if (!_getNodeString(newStart))
		{
			free(newStart);
			return (NULL);
		}
	}
	_linkNodes(newStart, *start);
	*start = newStart;
	return (newStart);
}

list_t *appendToTail(list_t **start, const char *text, int index)
{
	list_t *newNode, *node;

	if (!start)
		return (NULL);

	node = *start;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);

	_initializeNode(newNode, index);

	if (text)
	{
		_setNodeString(newNode, text);
		if (!_getNodeString(newNode))
		{
			free(newNode);
			return (NULL);
		}
	}

	if (node)
	{
		while (_hasNextNode(node))
			node = _getNextNode(node);
		_linkNodes(node, newNode);
	}
	else
		*start = newNode;

	return (newNode);
}

size_t printStringList(const list_t *list)
{
	size_t count = 0;

	while (list)
	{
		_printString(list->str ? list->str : "(nil)");
		_printString("\n");
		list = _getNextNode(list);
		count++;
	}
	return (count);
}

int removeNodeAtIndex(list_t **start, unsigned int index)
{
	list_t *node, *prevNode;
	unsigned int i = 0;

	if (!start || !*start)
		return (0);

	if (!index)
	{
		node = *start;
		*start = _getNextNode(node);
		_freeNodeString(node);
		free(node);
		return (1);
	}
	node = *start;
	while (node)
	{
		if (i == index)
		{
			prevNode->next = _getNextNode(node);
			_freeNodeString(node);
			free(node);
			return (1);
		}
		i++;
		prevNode = node;
		node = _getNextNode(node);
	}
	return (0);
}

void freeStringList(list_t **start)
{
	list_t *node, *nextNode, *listStart;

	if (!start || !*start)
		return;
	listStart = *start;
	node = listStart;
	while (node)
	{
		nextNode = _getNextNode(node);
		_freeNodeString(node);
		free(node);
		node = nextNode;
	}
	*start = NULL;
}

