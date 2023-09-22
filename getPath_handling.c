#include "shell.h"

/**
 * isExecutableCommand - determines if a file is an executable command
 * @data: The data structure
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isExecutableCommand(data_d *data, char *path)
{
	struct stat st;
	(void)data;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicateCharacters - duplicates characters from a string
 * @pathStr: The PATH string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Pointer to a new buffer
 */
char *duplicateCharacters(char *pathStr, int start, int stop)
{
	static char buffer[1024];
	int g = 0, w = 0;

	for (w = 0, g = start; g < stop; g++)
		if (pathStr[g] != ':')
			buffer[w++] = pathStr[g];
	buffer[w] = 0;
	return (buffer);
}

/**
 * findCommandPath - finds the command in the PATH string
 * @data: The data struct
 * @pathStr: The PATH string
 * @command: The command to find
 *
 * Return: Full path of the command if found, or NULL
 */
char *findCommandPath(data_d *data, char *pathStr, char *command)
{
	int g = 0, currentPos = 0;
	char *path;

	if (!pathStr)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (isExecutableCommand(data, command))
			return (command);
	}
	while (1)
	{
		if (!pathStr[g] || pathStr[g] == ':')
		{
			path = duplicateCharacters(pathStr, currentPos, g);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (isExecutableCommand(data, path))
				return (path);
			if (!pathStr[g])
				break;
			currentPos = g;
		}
		g++;
	}
	return (NULL);
}
