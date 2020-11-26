#include "shell.h"
/**
 * builtins - check if the input cmld is a builtin
 * @args: argument structure
 * Return: 0 if found
 */
int builtins(arguments_t *args)
{
	int idx = 0;

	builtins_t bDict[] = {
		{"env", _bEnv },
		{"exit", _bExit},
		{"setenv", _bSEnv},
		{"unsetenv", _bUEnv},
		{"help", _bHelp},
		{"cd", _bCd},
		{"alias", _bAlias},
		{"history", _bHist},
		{NULL, NULL}
	};

	while (bDict[idx].cmd)
	{
		if (!_strcmp(args->toks[0], bDict[idx].cmd))
		{
			return (bDict[idx].bfc(args));
		}
		idx++;
	}
	return (EXIT_FAILURE);
}

/**
 * _bEnv - built-in print environment variable
 * @args: argument structure
 * Return: Always 0
 */
int _bEnv(arguments_t *args)
{
	list_t *head = args->head;

	while (head)
	{
		_puts(head->str, 1);
		_puts("\n", 1);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}

/**
 * _bExit - built-in exit
 * @args: argument structure
 * Return: EXIT_FAILURE or no return since exit
 */

int _bExit(arguments_t *args)
{
	int exitN;
	int xStatus = args->exitS;

	if (args->toks[1]) /* there is an exit value */
	{
		exitN = _atoi(args->toks[1]);
		if (exitN <= 0) /* invalid number */
		{
			errno = EXITERR;
			printErr(args);
			return (0);
		}
		freeToks(args);
		freeEnv(args);
		freeAlias(args);
		exit(exitN);
	}
	freeToks(args);
	freeEnv(args);
	freeAlias(args);
	exit(xStatus);
}

/**
 * _bSEnv - sets enviroment variable
 * @args: Arguments structure
 * Return: 0
 */
int _bSEnv(arguments_t *args)
{
	char *buf = NULL;
	list_t *envv = NULL;

	if (!(args->toks[1]) || !(args->toks[2]))
	{
		errno = EINVAL;
		printErr(args);
		return (0);
	}
	buf = malloc(_strlen(args->toks[1]) + _strlen(args->toks[2]) + 2);
	if (!buf)
		return (EXIT_FAILURE);

	_strcpy(buf, args->toks[1]);
	_strcat(buf, "=");
	_strcat(buf, args->toks[2]);

	envv = _getenvLL(args->toks[1], args);

	if (envv) /* existing */
	{
		free(envv->str);
		envv->str = _strdup(buf);
		if (!envv->str)
			return (free(envv), EXIT_FAILURE);
		free(buf);
		return (EXIT_SUCCESS);
	}
	/* new variable */
	add_node_end(&(args->head), buf);
	free(buf);
	return (EXIT_SUCCESS);
}

/**
 * _bUEnv - removes an enviroment variable
 * @args: Arguments structure
 * Return: 0
 */
int _bUEnv(arguments_t *args)
{
	list_t *envv = args->head;
	size_t idx = 0;

	if (args->toks[1])
	{
		while (envv)
		{
			args->index = idx;
			if (!(_strncmp(envv->str, args->toks[1], _strlen(args->toks[1]))))
			{
				delete_node_at_index(&(args->head), idx);
				break;
			}
			envv = envv->next;
			idx++;
		}
		return (EXIT_SUCCESS);
	}
	errno = EINVAL;
	printErr(args);
	return (0);
}
