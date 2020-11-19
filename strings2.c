#include "shell.h"

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string.
 *
 * Return: 0 if the strings are similar,
 * the ASCII value of s1 - s2 otherwise.
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * _strncmp - compares two strings up to n bytes
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to compare
 *
 * Return: 0 if similar, -1 if not
 */
int _strncmp(char *s1, char *s2, unsigned int n)
{
        unsigned int idx = 0;

        for (; s1[idx] && s2[idx] && idx < n; idx++)
        {
                if (s1[idx] != s2[idx])
                        return (-1);
        }
        return (EXIT_SUCCESS);
}

/**
 * _strstr - locates a substring
 * @haystack: string to scan
 * @needle: string to find
 *
 * Return: point to the beginning of the located substring
 * or NULL if the substring is not found
 */

char *_strstr(char *haystack, char *needle)
{
	char *a, *b;

	b = needle;

	if (*b == 0)
		return (haystack);

	for ( ; *haystack != 0; haystack++)
	{
		if (*haystack != *b)
			continue;
		a = haystack;
		while (1)
		{
			if (*b == 0)
				return (haystack);
			if (*a++ != *b++)
				break;
		}
		b = needle;
	}
	return (0);
}
