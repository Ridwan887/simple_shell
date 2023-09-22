#include "shell.h"


/**
 * fetchHistoryFile - gets the history file
 * @data: parameter struct
 *
 * Return: allocated string containing history file
 */
char *fetchHistoryFile(data_d *data)
{
	char *historyFile, *homeDirectory;

	homeDirectory = obtainEnvironmentVariable(data, "HOME=");
	if (!homeDirectory)
		return (NULL);

	historyFile = allocateStr((_strlen(homeDirectory) + _strlen(HIST_FILE) + 2));
	if (!historyFile)
		return (NULL);

	historyFile[0] = 0;
	copyString(historyFile, homeDirectory);
	concatenateString(historyFile, "/");
	concatenateString(historyFile, HIST_FILE);

	return (historyFile);
}


/**
 * saveHistory - creates a file, or appends to an existing file
 * @data: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int saveHistory(data_d *data)
{
	ssize_t fileDescriptor;
	char *fileName = fetchHistoryFile(data);
	list_t *node = NULL;

	if (!fileName)
		return (-1);

	fileDescriptor = createFile(fileName, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fileName);
	if (fileDescriptor == -1)
		return (-1);

	for (node = data->history; node; node = node->next)
	{
		writeToFileDescriptor(node->str, fileDescriptor);
		writeToFileDescriptor("\n", fileDescriptor);
	}

	writeToFileDescriptor(FLUSH_BUFFER, fileDescriptor);
	close(fileDescriptor);
	return (1);
}

/**
 * loadHistory - reads history from file
 * @data: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int loadHistory(data_d *data)
{
	int historyCount = 0;
	ssize_t fileDescriptor;
	char *fileName = fetchHistoryFile(data);

	if (!fileName)
		return (0);

	fileDescriptor = openFile(fileName, O_RDONLY);
	free(fileName);
	if (fileDescriptor == -1)
		return (0);

	historyCount = loadHistoryFromFile(fileDescriptor, data);

	close(fileDescriptor);
	return (historyCount);
}

/**
 * appendHistoryEntry - adds entry to a history linked list
 * @data: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int appendHistoryEntry(data_d *data, char *buf, int linecount)
{
	list_t *node = NULL;

	if (data->history)
		node = data->history;
	addNodeToEnd(&node, buf, linecount);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @data: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumberHistory(data_d *data)
{
	list_t *node = data->history;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next;
	}

	return (data->historyCount = i);
}
