#include "shell.h"

char **getUnthinkableEnv(data_d *data)
{
    if (!data->envList || data->envModified)
    {
        data->envList = listToStrings(data->environment);
        data->envModified = 0;
    }

    return (data->envList);
}

int removeFromEnv(data_d *data, char *varName)
{
    list_t *node = data->environment;
    size_t index = 0;
    char *ptr;

    if (!node || !varName)
        return (0);

    while (node)
    {
        ptr = startsWith(node->str, varName);
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
    strcpy(newVar, varName);
    strcat(newVar, "=");
    strcat(newVar, varValue);
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
