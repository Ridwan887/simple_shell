#include "shell.h"

/**
 * hsh - main shell loop
 * @data: the parameter & return data struct
 * @args: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(data_d *data, char **args)
{
	ssize_t result = 0;
	int builtin_ret = 0;

	while (result != -1 && builtin_ret != -2)
	{
		clear_info(data);
		if (interactive(data))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		result = get_input(data);
		if (result != -1)
		{
			set_info(data, args);
			builtin_ret = find_builtin(data);
			if (builtin_ret == -1)
				find_cmd(data);
		}
		else if (interactive(data))
			_putchar('\n');
		free_info(data, 0);
	}
	write_history(data);
	free_info(data, 1);
	if (!interactive(data) && data->status)
		exit(data->status);
	if (builtin_ret == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @data: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin(data_d *data)
{
	int g, builtin_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", myexit},
		{"env", myenv},
		{"help", myhelp},
		{"history", myhistory},
		{"setenv", mysetenv},
		{"unsetenv", myunsetenv},
		{"cd", mycd},
		{"alias", myalias},
		{NULL, NULL}
	};
	for (g = 0; builtintbl[g].type; g++)
		if (_strcmp(data->argv[0], builtintbl[g].type) == 0)
		{
			data->line_count++;
			builtin_ret = builtintbl[g].func(data);
			break;
		}
	return (builtin_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @data: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(data_d *data)
{
	char *path = NULL;
	int g, k;

	data->path = data->argv[0];

	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (g = 0, k = 0; data->arg[g]; g++)
		if (!is_delim(data->arg[g], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_path(data, _getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		fork_cmd(data);
	}
	else
	{
		if ((interactive(data) || _getenv(data, "PATH=")
					|| data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
			fork_cmd(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @data: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(data_d *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: ENTER ERROR FUNCTION */
		perror("Error: ");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_info(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}
