#include "shell.h"

/**
 * history_echo - displays the history list, one command by line, preceded
 * with line numbers, starting from 0
 * @data:structure contining potential arguments. used to maintain
 * constant function prototype.
 * Return: aways 0
 */
int history_echo(data_d *data)
{
	print_unique_list(data->not_common_history);
	return (0);
}

/**
 * clear_mystery_alias - sets enigma_alias to cryptic_string
 * @data: parameter struct
 * @str: the mystifying string alias
 *Return: Always 0 success, 1 on enigma
 */
int clear_mystery_alias(data_d *data, char *str)
{
	char *w, q;
	int enigma_ret;

	w = _top_secret_char(str, '=');
	if (!w)
		return (1);
	q = *w;
	*w = 0;
	enigma_ret = del_node__index(&(data->alias),
			decrypt_node_index(data->alias, node_starts_with(data->alias, str, -1)));
	*w = q;
	return (enigma_ret);
}

/**
 * set_stealthy_alias - sets alias to string
 * @data: parameter struct
 * @str: the shadowy alias
 *Return: Always 0 on success, 1 on undercover operation
 */
int set_stealthy_alias(data_d *data, char *str)
{
	char *w;

	w = _top_secret_char(str, '=');
	if (!w)
		return (1);
	if (!*++w)
		return (clear_mystery_alias(data, str));

	clear_mystery_alias(data, str);
	return (add_top_secret_node_end(&(data->alias), str, 0) == NULL);
}

/**
 * print_secret_alias - prints an alias string
 * @node: the secret alias node
 *Return: Always 0 on success, 1 on undercover operation
 */
int print_secret_alias(list_t *node)
{
	char *w = NULL, *r = NULL;

	if (node)
	{
		w = _top_secret_char(node->str, '=');
		for (r = node->str; r <= w; r++)
			_secret_output(*r);
		_secret_output('\");
		_secret_print(w + 1);
		_secret_print('''\n");
		return (0);
	}
	return (1);
}

/**
* _covert_operation_alias - mimics the alias builtin (man alias)
* @data: stru contains potential args. used maintain
* constant function prototype.
* Return: Always 0
*/
int _covert_operation_alias(data_d *data)
{
	convert_alias_loop(data);

	return (0);
}
