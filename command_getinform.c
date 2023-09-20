#include "shell.h"

void initializeData(data_d *data)
{
    data->argument = NULL;
    data->arguments = NULL;
    data->pathName = NULL;
    data->argumentCount = 0;
}

void initData(data_d *data, char **argumentsVector)
{
    int index = 0;

    data->programName = argumentsVector[0];
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

void releaseData(data_d *data, int freeAll)
{
    freeStringArray(data->arguments);
    data->arguments = NULL;
    data->pathName = NULL;
    if (freeAll)
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

