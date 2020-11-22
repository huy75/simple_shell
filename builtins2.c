#include "shell.h"

/**
 * _bHelp - about builtin commands
 * @args: arguments structure
 * Return: 0
 */

int _bHelp(arguments_t *args)
{
	char **arg;
	char *bfc;

	arg = args->toks;
	if (!(arg[1]))
	{
		_puts("Please type 'help function' ", STDIN_FILENO);
		_puts("to find out more about the built-in ", STDIN_FILENO);
		_puts("functions:\n\n", STDIN_FILENO);
		_puts("env\nsetenv [name]\nunsetenv [name]\n", STDIN_FILENO);
		_puts("help [pattern...]\n", STDIN_FILENO);
		_puts("exit [n]\n", STDIN_FILENO);
		return (0);
	}

	bfc = arg[1];
	if (!_strcmp(bfc, "env"))
	{
		helpEnv();
		return (0);
	}
	if (!_strcmp(bfc, "setenv"))
	{
		helpSEnv();
		return (0);
	}
	if (!_strcmp(bfc, "unsetenv"))
	{
		helpUEnv();
		return (0);
	}
	if (!_strcmp(bfc, "help"))
        {
                helpHelp();
                return (0);
        }
        if (!_strcmp(bfc, "exit"))
        {
                helpExit();
                return (0);
        }
	return (0);
}
