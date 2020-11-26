#include "shell.h"

/**
  * get_del - get the right delimiter for tokens
  * @str: string to parse
  * @delim: list of delimiters
  * Return: the delimiter that appears first
  */

char get_del(char *str, const char *delim)
{
	int i = 0, j;

	while (str[i])
	{
		j = 0;
		while (delim[j])
		{
			if (str[i] == delim[j])
				return (delim[j]);
			j++;
		}
		i++;
	}
	return (delim[0]);
}

/**
  * _strtok_r - extract tokens from strings
  * @str: string to be parsed
  * @delim: delimiter that separate each token
  * Return: a token, or NULL if no more
  */

char *_strtok_r(char *str, const char *delim)
{
	static char *tmp;
	char *next = NULL;
	unsigned int dif = 0;
	char *token = NULL;
	char cdel = '\0';

	if (str != NULL)
		tmp = str;

	token = tmp;
	if (token == NULL)
		return (NULL);

	cdel = get_del(tmp, delim);
	next = _strchr(tmp, cdel);
	if (next != NULL)
	{
		dif = _strlen(tmp);
		dif -= _strlen(next);
		token = tmp;
		next++;
		tmp = next;
		token[dif] = '\0';
	}
	if (next == NULL)
	{
		token = tmp;
		tmp = NULL;
	}
	return (token);
}

/**
  * _strtok - gets tokens & makes sure they're not empty
  * @str: string to be parsed
  * @delim:  delimiter that separate each token
  * Return: a token, or NULL if no more
  */

char *_strtok(char *str, const char *delim)
{
	char *token;

	token = _strtok_r(str, delim);
	while (token)
	{
		if (token[0] != '\0')
			break;
		token = _strtok_r(NULL, delim);
	}
	return (token);
}
