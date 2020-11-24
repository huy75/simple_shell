#include "shell.h"

/**
  * aliasValue - get the alias value
  * @wholeAl: the entire alias var
  * Return: the alias value
  */

char *aliasValue(char *wholeAl)
{
	int i = 0;
	int len;
	char *tmp = wholeAl;

	while (tmp[i] != 39)
		i++;
	tmp = (tmp + i + 1);
	len = _strlen(tmp);
	tmp[len - 1] = '\0';
	return (tmp);
}

/**
  * checkAlias - checks if the command is an alias
  * args: args
  * Return: void
  */

void checkAlias(arguments_t *args)
{
	list_t *head;
	char **cmds = args->toks;
	int i = 0;
	char *aliasVal, *tmp;

	while (cmds[i] != NULL)
	{
		head = get_alias(cmds[i], args);
		if (head != NULL)
		{
			aliasVal = aliasValue(head->str);
			tmp = _strdup(aliasVal);
			_strcpy(cmds[i], tmp);
			free(tmp);
		}
		i++;
	}
}
