#include "shell.h"

/**
 * _strdup - malloc new str and copy *str into it
 * @str: the string
 * Return: pointer to new string
 */

char *_strdup(char *str)
{
	char *nstr = NULL;
	unsigned int idx, sl;

	if (!str)
		return (NULL);

	sl = _strlen(str);
	nstr = malloc(sl * sizeof(char) + 1);
	if (!nstr)
		return (NULL);

	for (idx = 0; idx < sl; idx++)
		nstr[idx] = str[idx];

	nstr[idx] = '\0';
	return (nstr);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination string
 * @src: the string that will be concatenated at the end of dest.
 * Return: char, a pointer to the dest string.
 */

char *_strcat(char *dest, char *src)
{
	char *tdst = dest;

	while (*tdst)
		tdst++;

	while (*src)
	{
		*tdst = *src;
		src++;
		tdst++;
	}

	*tdst = '\0';

	return (dest);
}
