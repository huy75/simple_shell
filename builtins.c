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
	exit(EXIT_SUCCESS);
}
