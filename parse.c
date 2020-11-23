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
	unsigned int nbTks = TOKENBUF;

	if (!buffer)
		return (av);

	av = malloc(sizeof(char *) * nbTks);
	if (!av)
		return (av);

	token = _strtok(buffer, DELIMITERS);
	for (idx = 0; token; idx++)
	{
		av[idx] = token;
		if ((idx + 1) == nbTks)
		{
			av = _realloc(av, sizeof(char) * nbTks, sizeof(char) * (nbTks + TOKENBUF));
			nbTks += TOKENBUF;
		}
		token = _strtok(NULL, DELIMITERS);
	}
	av[idx] = NULL;
	return (av);
}
