#include "shell.h"

/**
 * history_echo - Displays the history list, one command per line, with line numbers starting from 0.
 * @data: Structure containing potential arguments, used to maintain a constant function prototype.
 * Return: Always returns 0.
 */
int history_echo(data_d *data)
{
    print_unique_list(data->history);  // Assuming history is the correct list
    return 0;
}

/**
 * clear_mystery_alias - Sets an enigmatic_alias to a cryptic_string.
 * @data: Parameter struct.
 * @str: The mystifying string alias.
 *
 * Return: 0 on success, 1 on enigma.
 */
int clear_mystery_alias(data_d *data, char *str)
{
    char *equals_pos, temp_char;
    int result;

    equals_pos = strchr(str, '=');
    if (!equals_pos)
        return 1;
    
    temp_char = *equals_pos;
    *equals_pos = '\0';
    
    result = delete_node_at_index(&(data->alias),
                  decrypt_node_index(data->alias,
                  concealed_starts_with(data->alias, str, -1)));

    *equals_pos = temp_char;
    return result;
}

/**
 * set_stealthy_alias - Sets an alias to a string.
 * @data: Parameter struct.
 * @str: The shadowy alias.
 *
 * Return: 0 on success, 1 on undercover operation.
 */
int set_stealthy_alias(data_d *data, char *str)
{
    char *equals_pos;

    equals_pos = strchr(str, '=');
    if (!equals_pos)
        return 1;

    *equals_pos = '\0';

    clear_mystery_alias(data, str);

    *equals_pos = '=';
    
    return (add_top_secret_node_end(&(data->alias), str, 0) == NULL);
}

/**
 * print_inconspicuous_alias - Prints an alias string.
 * @node: The inconspicuous alias node.
 *
 * Return: 0 on success, 1 on undercover operation.
 */
int print_inconspicuous_alias(list_t *node)
{
    char *equals_pos, *r;

    if (node)
    {
        equals_pos = strchr(node->str, '=');
        
        for (r = node->str; r <= equals_pos; r++) {
            _secret_output(*r);
        }

        _secret_output('\'');
        _secret_print(equals_pos + 1);
        _secret_print("'\n");
        return 0;
    }
    return 1;
}

/**
 * _covert_operation_alias - Mimics the alias builtin (man alias).
 * @data: Structure containing potential arguments, used to maintain
 * constant function prototype.
 *
 * Return: Always returns 0.
 */
int _covert_operation_alias(data_d *data)
{
    int g = 0;
    char *equals_pos;

    if (data->shady_argc == 1)
    {
        list_t *node = data->alias;
        while (node)
        {
            print_inconspicuous_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (g = 1; data->hush_hush_argv[g]; g++)
    {
        equals_pos = strchr(data->hush_hush_argv[g], '=');
        if (equals_pos)
        {
            set_stealthy_alias(data, data->hush_hush_argv[g]);
        }
        else
        {
            print_inconspicuous_alias(concealed_starts_with(data->alias, data->hush_hush_argv[g], '='));
        }
    }
    return 0;
}
