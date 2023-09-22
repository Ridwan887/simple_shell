#include "shell.h"

/**
 * exit_shell - Exits the shell with a specified exit status.
 * @data: Structure containing potential arguments and other data.
 * Return: Exits with the specified exit status.
 */
int exit_shell(data_d *data)
{
    if (data->arguments[1]) {
        int exit_status = custom_atoi(data->arguments[1]);
        if (exit_status == -1) {
            data->status = 2;
            print_error(data, "Illegal number: ");
            print_string(data->arguments[1]);
            print_char('\n');
        }
        data->error_number = exit_status; // Set the error number
    } else {
        data->error_number = 0; // No argument, set to 0
    }

    return data->error_number;
}

/**
 * change_directory_function - Changes the current directory of the shell process.
 * @data: Structure containing potential arguments and other data.
 * Return: Returns 0 on success, -1 on failure.
 */
int change_directory_function(data_d *data)
{
    char *target_directory = NULL;

    if (!data->arguments[1]) {
        target_directory = get_env_vari(data, "HOME=");
        if (!target_directory) {
            // Handle failure to retrieve home directory
            print_string("Error: Home directory not found\n");
            return -1;
        }
    } else if (custom_strcmp(data->arguments[1], "-") == 0) {
        target_directory = get_env_vari(data, "OLDPWD=");
        if (!target_directory) {
            // Handle failure to retrieve previous directory
            print_string("Error: Previous directory not found\n");
            return -1;
        }
    } else {
        target_directory = data->arguments[1];
    }

    if (chdir(target_directory) == -1) {
        // Handle directory change failure
        print_error(data, "Can't cd to ");
        print_string(target_directory);
        print_char('\n');
        return -1;
    }

    // Update environment variables
    set_env_variable(data, "OLDPWD", get_env_vari(data, "PWD="));
    set_env_variable(data, "PWD", getcwd(NULL, 0));

    return 0; // Successful directory change
}

/**
 * help_command - Displays a help message.
 * @data: Structure containing potential arguments and other data.
 * Return: Always returns 0.
 */
int help_command(data_d *data)
{
    // Implement help functionality here with meaningful messages
    print_string("help call works. Function not yet implemented .\n");
    return 0;
}
