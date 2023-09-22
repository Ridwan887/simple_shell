#include "shell.h"

/**
 * initialize_data - intializes data_d structure
 * @data: structure of address
 */
void initialize_data(data_d *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->pathName = NULL;
	data->argc = 0;
}

/**
 * initData - initializes data_d struct
 * @data: struct of address
 * @av: argument vector
*/
void initData(data_d *data, char **av)
{
	int index = 0;

	data->programName = av[0];
	if (data->argument)
	{
		data->arguments = stringSplit(data->argument, " \t");
		if (!data->arguments)
		{
			data->arguments = malloc(sizeof(char *) * 2);
			if (data->arguments)
			{
				data->arguments[0] = stringDuplicate(data->argument);
				data->arguments[1] = NULL;
			}
		}
		for (index = 0; data->arguments && data->arguments[index]; index++)
			;
		data->argumentCount = index;
		substituteAlias(data);
		substituteVariables(data);
	}
}

/**
 * release_data - frees data_d struct fields
 * @data: struct of address
 * @all: true if freeing all fields
 */
void release_data(data_d *data, int all)
{
	freeStringArray(data->arguments);
	data->arguments = NULL;
	data->pathName = NULL;
	if (all)
	{
		if (!data->commandBuffer)
			free(data->argument);
		if (data->environment)
			freeList(&(data->environment));
		if (data->commandHistory)
			freeList(&(data->commandHistory));
		if (data->commandAlias)
			freeList(&(data->commandAlias));
		freeStringArray(data->environmentList);
		data->environmentList = NULL;
		freePointerArray((void **)data->commandBuffer);
		if (data->readFileDescriptor > 2)
			close(data->readFileDescriptor);
		writeCharacter(BUF_FLUSH);
	}
}

