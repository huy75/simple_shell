#include "shell.h"

/**
  * print_alias - prints all alias
  * @args: args
  * Return: void
  */

void print_alias(arguments_t *args)
{
	list_t *head = args->head_alias;
	char *str;
	int i;

	if (head == NULL)
		return;
	while (head)
	{
		i = 0;
		str = head->str;
		while (str[i])
		{
			_putchar(str[i], 1);
			if (str[i] == '=')
				_putchar(39, 1);
			i++;
		}
		_putchar(39, 1);
		_puts("\n", 1);
		head = head->next;
	}
}

/**
  * scan_match - compares alias variables
  * @a: string 1
  * @b: string 2
  * @args: args
  * Return: 0 if a = b or 1 otherwise
  */

int scan_match(char *a, char *b, arguments_t *args)
{
	int i;

	if (_strcmp(args->toks[0], "alias") == 0)
	{
		i = 0;
		while (a[i] != '=')
			i++;
		if (_strncmp(a, b, i) == 0)
			return (0);
		else
			return (1);
	}
	if (_strcmp(a, b) == 0)
		return (0);
	return (1);
}

/**
  * get_alias - looks for existing alias
  * @comp: alias to compar with
  * @args: args
  * Return: pointer to node containing comp or NULL otherwise
  */

list_t *get_alias(char *comp, arguments_t *args)
{
	list_t *head = args->head_alias;
	int cmp;

	if (head == NULL)
		return (NULL);
	while (head)
	{
		cmp = scan_match(comp, head->str, args);
		if (cmp == 0)
		{
			return (head);
		}
		head = head->next;
	}
	return (NULL);
}

/**
  * setup_alias - setup an alias
  * or overwrites it if it exists
  * @args: args
  * @alias: alias to setup
  * Return: void
  */

void setup_alias(arguments_t *args, char *alias)
{
	list_t *head;

	head = get_alias(alias, args);
	if (head == NULL)
	{
		add_node_end(&(args->head_alias), alias);
	}
	else
	{
		free(head->str);
		head->str = _strdup(alias);
		if (!head->str)
		{
			free(head);
			return;
		}
	}
}

/**
  * freeAlias - free all alias
  * @args: args
  * Return: void
  */

void freeAlias(arguments_t *args)
{
	list_t *current = args->head_alias;
	list_t *next;

	if (!(args->head_alias))
		return;

	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	args->head_alias = NULL;
}
