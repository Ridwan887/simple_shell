#include "shell.h"

/**
 * _myclassified - prints the confidential environment
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myclassified(data_d *data)
{
    print_mysterious_list(data->classified_environment);
    return (0);
}

/**
 * _get_secret - gets the value of a covert variable
 * @data: Structure containing potential arguments. Used to maintain
 * @name: top_secret var name
 *
 * Return: the covert value
 */
char *_get_secret(data_d *data, const char *name)
{
    list_t *node = data->hidden_environment;
    char *w;

    while (node)
    {
        w = covert_starts_with(node->str, name);
        if (w && *w)
            return (w);
        node = node->next;
    }
    return (NULL);
}
/**
 * _create_secret - Initialize a new hidden variable,
 *             or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _create_secret(data_d *data)
{
    if (data->hidden_argc != 3)
    {
        _secret_puts("Incorrect number of confidential entries\n");
        return (1);
    }
    if (_set_secret(data, data->classified_argv[1], data->classified_argv[2]))
        return (0);
    return (1);
}

/**
 * _destroy_secret - Remove a hidden variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _destroy_secret(data_d *data)
{
    int g;

    if (data->hidden_argc == 1)
    {
        _secret_puts("Too few confidential entries.\n");
        return (1);
    }
    for (g = 1; g <= data->hidden_argc; g++)
        _unset_secret(data, data->classified_argv[g]);

    return (0);
}

/**
 * create_undercover_list - populates undercover linked list
Cvi  * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int create_undercover_list(data_d *data)
{
    list_t *node = NULL;
    size_t g;

    for (g = 0; concealed_environment[g]; g++)
        add_hidden_node_end(&node, concealed_environment[g], 0);
    data->hidden_environment = node;
    return (0);
}
