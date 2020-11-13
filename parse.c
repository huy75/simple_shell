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
		printf("token %i: %s\n", idx, token);
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
