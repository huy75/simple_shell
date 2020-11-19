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
		{"exit",_bExit},
		{"setenv", _bSEnv},
		{"unsetenv", _bUEnv},
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
 * Return: 0
 */

int _bExit(arguments_t *args)
{
	free(args->buf);
	free_listint_safe(&(args->head));
	exit(EXIT_SUCCESS);
}

/**
 * _bSEnv - sets enviroment variable
 * @args: Arguments structure
 * Return: 0 on success
 */
int _bSEnv(arguments_t *args)
{
	char *buf = NULL;
	list_t *envv;

	if (!(args->toks[1]) || !(args->toks[2]))
	      return (1);

        buf = malloc(_strlen(args->toks[1]) + _strlen(args->toks[2]) + 2);
	if (!buf)
		return (1);

       	_strcpy(buf, args->toks[1]);
       	buf = str_concat(buf, "=");
       	buf = str_concat(buf, args->toks[2]);

        envv = _getenvLL(args->toks[1], args);
        if (envv)
	{
		free(envv->str);
		envv->str = buf;
		free(buf);
		return (EXIT_SUCCESS);
	}
	add_node_end(&(args->head), buf);
	free(buf);
	return (EXIT_SUCCESS);
}

/**
 * _bUEnv - removes an enviroment variable
 * @args: Arguments structure
 * Return: 0 on success
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
		return (0);
	}
	return (1);
}
