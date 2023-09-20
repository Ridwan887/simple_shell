#include "shell.h"

/**
 * exit_shell - exits the shell
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if data->arguments[0] != "exit"
 */
int exit_shell(data_d *data)
{
    int exit_status;

    if (data->arguments[1]) /* If there is an exit argument */
    {
        exit_status = custom_atoi(data->arguments[1]);
        if (exit_status == -1)
        {
            data->status = 2;
            print_error(data, "Illegal number: ");
            print_string(data->arguments[1]);
            print_char('\n');
            return (1);
        }
        data->error_number = custom_atoi(data->arguments[1]);
        return (-2);
    }
    data->error_number = -1;
    return (-2);
}

/**
 * change_directory_function - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int change_directory_function(data_d *data)
{
    char *current_directory, *target_directory, buffer[1024];
    int change_directory_result;

    current_directory = getcwd(buffer, 1024);
    if (!current_directory)
        print_string("TODO: >>getcwd failure message here<<\n");
    if (!data->arguments[1])
    {
        target_directory = get_env_variable(data, "HOME=");
        if (!target_directory)
            change_directory_result = /* TODO: what should this be? */
                change_directory_function((target_directory = get_env_variable(data, "PWD=")) ? target_directory : "/");
        else
            change_directory_result = change_directory_function(target_directory);
    }
    else if (custom_strcmp(data->arguments[1], "-") == 0)
    {
        if (!get_env_variable(data, "OLDPWD="))
        {
            print_string(current_directory);
            print_char('\n');
            return (1);
        }
        print_string(get_env_variable(data, "OLDPWD="));
        print_char('\n');
        change_directory_result = /* TODO: what should this be? */
            change_directory_function((target_directory = get_env_variable(data, "OLDPWD=")) ? target_directory : "/");
    }
    else
        change_directory_result = change_directory_function(data->arguments[1]);
    if (change_directory_result == -1)
    {
        print_error(data, "can't cd to ");
        print_string(data->arguments[1]);
        print_char('\n');
    }
    else
    {
       set_env_variable(data, "OLDPWD", get_env_variable(data, "PWD="));
        set_env_variable(data, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * help_command - displays a help message
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int help_command(data_d *data)
{
    char **argument_array;

    argument_array = data->arguments;
    print_string("help call works. Function not yet implemented \n");
    if (0)
        print_string(*argument_array); /* temp att_unused workaround */
    return (0);
}
