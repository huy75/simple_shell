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

/**
 * _strchr2 - locates a character in a string.
 * @s: the string
 * @c: the character
 * Return: a pointer to the first occurence + 1 or NULL if not found.
 */

char *_strchr2(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
		{
			s++;
			return (s);
		}
		s++;
	}
	if (*s == c)
	{
		s++;
		return (s);
	}
	return (0);
}
