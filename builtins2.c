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
		_puts("exit [n]\n", STDIN_FILENO);
		_puts("help [pattern...]\ncd [directory]\n", STDIN_FILENO);
		_puts("history\n", STDIN_FILENO);
		return (0);
	}

	bfc = arg[1];
	if (!_strcmp(bfc, "env"))
		helpEnv();
	if (!_strcmp(bfc, "setenv"))
		helpSEnv();
	if (!_strcmp(bfc, "unsetenv"))
		helpUEnv();
	if (!_strcmp(bfc, "exit"))
		helpExit();
	if (!_strcmp(bfc, "help"))
		helpHelp();
	if (!_strcmp(bfc, "cd"))
		helpCd();
	if (!_strcmp(bfc, "history"))
		helpHist();
	return (0);
}

/**
  * arrange_env - updates PwD and OLDPWD if successful cd
  * @new_pwd: new PWD val
  * @old_pwd: old PWD val
  * @args: args
  * Return: void
  */

void arrange_env(char *new_pwd, char *old_pwd, arguments_t *args)
{
	args->toks[1] = "PWD";
	args->toks[2] = new_pwd;
	_bSEnv(args);
	args->toks[1] = "OLDPWD";
	args->toks[2] = old_pwd;
	_bSEnv(args);
}

/**
  * _bCd - changes current directory to args->toks[1]
  * @args: args
  * Return: 0 on failure, EXIT_SUCCESS on succes
  */

int _bCd(arguments_t *args)
{
	char old_pwd[120];
	char *new_pwd;


	(void)args;

	getcwd(old_pwd, 120);
	if (args->toks[1] == NULL)
	{
		new_pwd = _getenvVAL("HOME", args);
		chdir(new_pwd);
		arrange_env(new_pwd, old_pwd, args);
	}
	else if (args->toks[1][0] == '-')
	{
		new_pwd = _getenvVAL("OLDPWD", args);
		chdir(new_pwd);
		arrange_env(new_pwd, old_pwd, args);
	}
	else
	{
		new_pwd = args->toks[1];
		if (chdir(new_pwd) == -1)
		{
			errno = ENOTDIR;
			printErr(args);
			return (0);
		}
		arrange_env(new_pwd, old_pwd, args);
	}
	return (EXIT_SUCCESS);
}
/**
  * _bAlias - setsup, prints, overwrites aliases
  * @args: args
  * Return: EXIT_SUCCESS
  */

int _bAlias(arguments_t *args)
{
	if (args->toks[1] == NULL)
	{
		print_alias(args);
	}
	if (args->toks[1] != NULL)
	{
		setup_alias(args);
	}
	return (EXIT_SUCCESS);
}
