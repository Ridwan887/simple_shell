#include "shell.h"

char *fetchHistoryFile(data_d *data)
{
	char *historyFile, *homeDirectory;

	homeDirectory = obtainEnvironmentVariable(data, "HOME=");
	if (!homeDirectory)
		return (NULL);

	historyFile = allocateString((_strlen(homeDirectory) + _strlen(HISTORY_FILENAME) + 2));
	if (!historyFile)
		return (NULL);

	historyFile[0] = 0;
	copyString(historyFile, homeDirectory);
	concatenateString(historyFile, "/");
	concatenateString(historyFile, HISTORY_FILENAME);

	return (historyFile);
}

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

int loadHistory(data_d *data)
{
	int i, last = 0, lineCount = 0;
	ssize_t fileDescriptor, bytesRead, fileSize = 0;
	struct stat fileInfo;
	char *buffer = NULL, *fileName = fetchHistoryFile(data);

	if (!fileName)
		return (0);

	fileDescriptor = openFile(fileName, O_RDONLY);
	free(fileName);
	if (fileDescriptor == -1)
		return (0);

	if (!getFileStatus(fileDescriptor, &fileInfo))
		fileSize = fileInfo.st_size;

	if (fileSize < 2)
		return (0);

	buffer = allocateString((fileSize + 1));
	if (!buffer)
		return (0);

	bytesRead = readFromFileDescriptor(fileDescriptor, buffer, fileSize);
	buffer[fileSize] = 0;

	if (bytesRead <= 0)
		return (free(buffer), 0);

	close(fileDescriptor);

	for (i = 0; i < fileSize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			addHistoryEntry(data, buffer + last, lineCount++);
			last = i + 1;
		}

	if (last != i)
		addHistoryEntry(data, buffer + last, lineCount++);

	free(buffer);
	data->historyCount = lineCount;

	while (data->historyCount-- >= HISTORY_MAX)
		removeNodeAtIndex(&(data->history), 0);

	renumberHistory(data);
	return (data->historyCount);
}

int appendHistoryEntry(data_d *data, char *buffer, int lineCount)
{
	list_t *node = NULL;

	if (data->history)
		node = data->history;

	addNodeToEnd(&node, buffer, lineCount);

	if (!data->history)
		data->history = node;
	return (0);
}

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
