#include "shell.h"

/**
 * cpyEnv - copies env to linked list
 * Return: Pointer to first node
 */
list_t *cpyEnv(void)
{
        int idx = 0;
        list_t *head = NULL;

        while (environ[idx])
        {
                add_node_end(&head, environ[idx]);
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
