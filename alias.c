#include "shell.h"

/**
  * print_alias - prints all alias
  * @args: args
  * Return: void
  */

void print_alias(arguments_t *args)
{
	list_t *head = args->head_alias;

	if (head == NULL)
		return;
	while (head)
	{
		_puts(head->str, 1);
		_puts("\n", 1);
		head = head->next;
	}
}

/**
  * scan_match - compares alias variables
  * @a: string 1
  * @b: string 2
  * Return: 0 if a = b or 1 otherwise
  */

int scan_match(char *a, char *b)
{
	char var1[100];
	char var2[100];
	int i;

	for (i = 0; a[i] != '='; i++)
		var1[i] = a[i];
	for (i = 0; b[i] != '='; i++)
		var2[i] = b[i];

	if (_strcmp(var1, var2) == 0)
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
		cmp = scan_match(comp, head->str);
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
  * Return: void
  */

void setup_alias(arguments_t *args)
{
	list_t *head;

	head = get_alias(args->toks[1], args);
	if (head == NULL)
	{
		add_node_end(&(args->head_alias), args->toks[1]);
	}
	else
	{
		free(head->str);
		head->str = _strdup(args->toks[1]);
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
