#include "shell.h"

/**
 * getUnthinkableEnv - returns the string array copy of our environ
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
char **getUnthinkableEnv(data_d *data)
{
	if (!data->envList || data->envModified)
	{
		data->envList = listToStrings(data->environment);
		data->envModified = 0;
	}
	return (data->envList);
}

/**
 * removeFromEnv - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int removeFromEnv(data_d *data, char *var)
{
	list_t *node = data->environment;
	size_t index = 0;
	char *ptr;
	
	if (!node || !var)
		return (0);
	while (node)
	{
		ptr = startsWith(node->str, var);
		if (ptr && *ptr == '=')
		{
			data->envModified = deleteNodeAtIndex(&(data->environment), index);
			index = 0;
			node = data->environment;
			continue;
		}
		node = node->next;
		index++;
	}
	return (data->envModified);
}

/**
 * setUnthinkableEnv - Initialize a new environment variable,
 *             or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int setUnthinkableEnv(data_d *data, char *varName, char *varValue)
{
	char *newVar = NULL;
	list_t *node;
	char *ptr;
	if (!varName || !varValue)
		return (0);
	newVar = malloc(strlen(varName) + strlen(varValue) + 2);

	if (!newVar)
		return (1);
	_strcpy(newVar, varName);
	_strcat(newVar, "=");
	_strcat(newVar, varValue);
	node = data->environment;
	while (node)
	{
		ptr = startsWith(node->str, varName);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = newVar;
			data->envModified = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(data->environment), newVar, 0);
	free(newVar);
	data->envModified = 1;
	return (0);
}
