#include "shell.h"

/**
 * cpyEnv - copies env to linked list
 * @args: the arguments
 * Return: Pointer to first node
 */
list_t *cpyEnv(arguments_t *args)
{
	int idx = 0;
	list_t *head = NULL;

	while (args->env[idx])
	{
		add_node_end(&head, args->env[idx]);
		idx++;
	}
	return (head);
}

/**
 * add_node_end - adds a node at the end of list
 * @head: points to the head of list
 * @str: what goes in the new node
 * Return: address of new node or NULL
 */
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *newTail;
	list_t *ptr = *head;

	if (!head || !str)
		return (NULL);

	newTail = malloc(sizeof(list_t));
	if (!newTail)
		return (NULL);

	newTail->str = strdup(str);
	if (!newTail->str)
	{
		free(newTail);
		return (NULL);
	}

	newTail->next = NULL;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = newTail;
	}
	else
		*head = newTail;
	return (newTail);
}

/**
 * _getenvLL - gets an env variable from a name
 * @name: char * to search for
 * @args: args
 * Return: char * containing nodes value, NULL if not found
 */
list_t *_getenvLL(char *name, arguments_t *args)
{
	list_t *head = args->head;

	while (head)
	{
		if (!_strcmp(name, head->str))
		{
			return (head);
		}
		head = head->next;
	}
	return (NULL);
}

/**
 * delete_node_at_index - deletes the node at index of the linked list.
 * @head: points to the head of the list
 * @index: the index of the node to delete
 * Return: 1 if it succeeded, -1 if it failed
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	unsigned int idx = 0;
	list_t *node;
	list_t *ptr = *head;

	if (!head || !*head)
		return (-1);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node);
		return (1);
	}

	while (ptr)
	{
		if (idx == index)
		{
			node->next = ptr->next;
			free(ptr);
			return (1);
		}
		node = ptr;
		ptr = ptr->next;
		idx++;
	}
	return (-1);
}

/**
 * free_list2 - frees all nodes of a list
 * @head: point the head of list
 * Return: void
 */
void free_list2(list_t **head)
{
	list_t *next, *ptr;

	if (!head)
		return;

	next = *head;
	while (next)
	{
		ptr = next;
		next = next->next;
		free(ptr->str);
		free(ptr);
	}
	*head = NULL;
}
