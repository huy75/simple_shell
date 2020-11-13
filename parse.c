#include "shell.h"

/**
 * parseBuffer - parse a buffer into an array of pointers
 * @buffer: input buffer
 * Return: an array of pointers to char
 */
char **parseBuffer(char *buffer)
{
	char **av = NULL, *token = NULL;
	unsigned int idx;
	unsigned int modTks = 5;

	if (!buffer)
		return (av);

	av = malloc(sizeof(char *) * modTks);
	if (!av)
		return (av);

	token = strtok(buffer, DELIMITERS);

	for (idx = 0; token; idx++)
	{
		printf("token: %s\n", token);
		av[idx] = token;
/*
		if ((idx + 1) == modTks)
			_realloc(av, sizeof(char) * modTks, sizeof(char) * (2 * modTks));
*/
		token = strtok(NULL, DELIMITERS);
	}
	av[idx] = NULL;
	return (av);
}

/**
 * freeToken - free
 * @token: input command
 * Return: void
 */
void freeToken(char **token)
{
	unsigned int idx = 0;

	if (token)
	{
		while (token[idx])
		{
			printf("idx: %i\n", idx);
			free(token[idx]);
			idx++;
		}
		free(token);

	}
}
