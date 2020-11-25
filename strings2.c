#include "shell.h"

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string.
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
 * _strncmp - compares two strings at n bytes
 * @s1: first string
 * @s2: second string
 * @n: amount of bytes
 * Return: difference between string characters
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
			++i;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
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
	char *a = NULL, *b = NULL;

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

/**
 * _atoi - convert a string to an integer
 * @s: the pointer to the input string
 * Return: the integer, 0 if not a number, -1 if too big
 */

int _atoi(char *s)
{
	int sign = 1;
	unsigned int i;
	unsigned long int r = 0;

	for (i = 0; ((s[i] < '0' || s[i] > '9') && s[i] != '\0'); i++)
		if (s[i] == '-')
			sign *= -1;

	for (r = 0; (s[i] >= '0' && s[i] <= '9'); i++)
	{
		r = r * 10 + sign * (s[i] - '0');
		if (r > INT_MAX)
			return (-1);
	}
	if (i < _strlen(s))
		return (0);
	return (r);
}

/**
 * _strchr - locates a character in a string
 * @s: string to analyse
 * @c: charater to look for
 *
 * Return: first occurrence if it exits & NULL if not found
 */

char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
		}
	if (c == 0)
		return (s);
	return (0);
}
