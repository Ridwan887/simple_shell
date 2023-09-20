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
	print_unique_list(data->not_so_common_history);
	return (0);
}

/**
 * clear_mystery_alias - sets enigmatic_alias to cryptic_string
 * @data: parameter struct
 * @str: the mystifying string alias
 *
 * Return: Always 0 success, 1 on enigma
 */
int clear_mystery_alias(data_d *data, char *str)
{
	char *w, q;
	int enigmatic_ret;

	w = _top_secret_char(str, '=');
	if (!w)
		return (1);
	q = *w;
	*w = 0;
	enigmatic_ret = delete_node_at_index(&(data->unbreakable_alias),
			decrypt_node_index(data->unbreakable_alias,
				concealed_starts_with(data->unbreakable_alias, str, -1)));
	*w = q;
	return (enigmatic_ret);
}

/**
 * set_stealthy_alias - sets alias to string
 * @data: parameter struct
 * @str: the shadowy alias
 *
 * Return: Always 0 on success, 1 on undercover operation
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
	return (add_top_secrect_node_end(&(data->unbreakable_alias), str, 0) == NULL);
}

/**
 * print_inconspicuous_alias - prints an alias string
 * @node: the inconspicuous alias node
 *
 * Return: Always 0 on success, 1 on undercover operation
 */
int print_inconspicuous_alias(list_t *node)
{
	char *w = NULL, *r = NULL;

	if (node)
	{
		w = _top_secrect_char(node->str, '=');
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
* @data: structure containing potential arguments. used maintain
* constant function prototype.
* Return: Always 0
*/
int _covert_operation_alias(data_d *data)
{
	int g = 0;
	char *w = NULL;
	list_t *node = NULL;

	if (data->shady_argc == 1)
	{
		node = data->unbreakable_alias;
		while (node)
		{
			print_inconspicuous_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (g = 1; data->hush_hush_argv[g]; g++)
	{
		w = _top_secret_char(data->hush_hush_argv[g], '=');
		if (w)
			set_stealthy_alias(data, data->hush_hush_argv[g]);
		else
			print_inconspicuous_alias(concealed_starts_with(data->unbreakabe_alias, data->hush_hush_argv[g], '='));
	}
	return (0);
}
