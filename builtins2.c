#include "shell.h"

/**
 * _bHelp - about builtin commands
 * @args: arguments structure
 * Return: 0
 */

int _bHelp(arguments_t *args)
{
	char **arg = NULL;
	char *bfc = NULL;

	arg = args->toks;
	if (!(arg[1]))
	{
		_puts("Please type 'help function' ", STDIN_FILENO);
		_puts("to find out more about the built-in ", STDIN_FILENO);
		_puts("functions:\n", STDIN_FILENO);
		_puts("env\nsetenv [name]\nunsetenv [name]\n", STDIN_FILENO);
		_puts("exit [n]\n", STDIN_FILENO);
		_puts("help [pattern...]\ncd [directory]\n", STDIN_FILENO);
		_puts("alias or alias name=\'value\'\n", STDIN_FILENO);
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
	if (!_strcmp(bfc, "alias"))
		helpAlias();
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
	char old_pwd[120] = "";
	char *new_pwd = NULL;

	getcwd(old_pwd, 120);
	if (args->toks[1] == NULL)
	{
		new_pwd = _getenvLL2("HOME", args);
		if (new_pwd == NULL)
			return (0);
		chdir(new_pwd);
		arrange_env(new_pwd, old_pwd, args);
	}
	else if (_strcmp(args->toks[1], "-") == 0)
	{
		new_pwd = _getenvLL2("OLDPWD", args);
		if (new_pwd == NULL)
		{
			_puts(old_pwd, 1);
			_putchar('\n', 1);
			return (0);
		}
		chdir(new_pwd);
		_puts(new_pwd, 1), _putchar('\n', 1);
		arrange_env(new_pwd, old_pwd, args);
	}
	else
	{
		new_pwd = args->toks[1];
		if (chdir(new_pwd) == -1)
		{
			errno = ENOTDIR, printErr(args);
			return (0);
		}
		else
		{
			arrange_env(new_pwd, old_pwd, args);
		}
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
	int i;

	if (args->toks[1] == NULL)
	{
		print_alias(args);
	}

	for (i = 1; args->toks[i]; i++)
	{
		if (_strchr(args->toks[i], '=') != NULL)
			setup_alias(args, args->toks[i]);
		else
			print_uniq_alias(args, args->toks[i]);
	}
	return (EXIT_SUCCESS);
}

/**
 * _bHist - about history builtin command
 * @args: arguments structure
 * Return: 0
 */

int _bHist(arguments_t *args)
{
	char *envH = NULL, *fileN = NULL, *line = NULL;
	char buf[HISTSIZE] = {0};
	int fd, lCnt = 0;
	ssize_t bytes;

	envH = _getenv("HOME", args->env);
	fileN = malloc(_strlen(envH) + _strlen(HISTORY) + 2);
	if (!fileN)
		return (free(envH), EXIT_FAILURE);

	_strcpy(fileN, envH), _strcat(fileN, "/"), _strcat(fileN, HISTORY);

	fd = open(fileN, O_RDONLY);
	if (fd == -1)
	{
		free(envH), free(fileN);
		return (0);
	}
	bytes = read(fd, buf, HISTSIZE);
	if (bytes == -1)
	{
		free(envH), free(fileN);
		close(fd);
		return (0);
	}
	buf[bytes + 1] = '\0';

	line = _strtok(buf, "\n");
	while (line != NULL)
	{
		print_number(lCnt);
		_puts(" ", STDOUT_FILENO);
		_puts(line, STDOUT_FILENO);
		_puts("\n", STDOUT_FILENO);
		lCnt++;
		line = _strtok(NULL, "\n");
	}
	free(envH), free(fileN), close(fd);
	return (0);
}
