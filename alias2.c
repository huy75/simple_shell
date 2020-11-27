#include "shell.h"

/**
  * aliasValue - get the alias value
  * @wholeAl: the entire alias var
  * Return: the alias value
  */

char *aliasValue(char *wholeAl)
{
	char *tmp = wholeAl;
	char *result;
	int i = 0;

	while (tmp[i] != '=')
	{
		i++;
	}
	tmp += i + 1;
	result = _strdup(tmp);
	return (result);
}

/**
  * checkAlias - checks if the command is an alias
  * @args: args
  * Return: void
  */

void checkAlias(arguments_t *args)
{
	list_t *head;
	char **cmds = args->toks;
	int i = 0;
	char *tmp;

	if (_strcmp(cmds[0], "alias") == 0)
		return;
	while (cmds[i] != NULL)
	{
		head = get_alias(cmds[i], args);
		if (head != NULL)
		{
			tmp = aliasValue(head->str);
			free(args->toks[0]);
			args->toks[0] = _strdup(tmp);
			free(tmp);
		}
		i++;
	}
}

/**
  * print_uniq_alias - prints unique alias
  * @args: agrs
  * @alias: the alias to print
  * Return: void
  */

void print_uniq_alias(arguments_t *args, char *alias)
{
	list_t *head = args->head_alias;
	char *str;
	int i;

	if (head == NULL)
		return;
	while (head)
	{
		str = head->str;
		if (_strcmp(alias, str) == 0)
		{
			i = 0;
			while (str[i])
			{
				_putchar(str[i], 1);
				if (str[i] == '=')
					_putchar(39, 1);
				i++;
			}
			_putchar(39, 1);
			_puts("\n", 1);
		}
		head = head->next;
	}
}
