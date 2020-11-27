#include "shell.h"

/**
* *_strcpy - copies string src to buffer pointed by dest
* @dest: destination
* @src: string to send
*
* Return: the string sent
*/

char *_strcpy(char *dest, char *src)
{
	unsigned int len = _strlen(src) - 1;
	unsigned int i;

	dest[len + 1] = '\0';
	for (i = 0; i <= len; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

/**
 * _getline - get line input from user
 * @lineptr: buffer where to send input
 * @n: size of buffer to modify
 * @stream: stream where to read
 * Return: number of chars read
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char tmp;
	int i = 0, re, size = 1;

	(void)stream;

	*lineptr = malloc(sizeof(char) * 1);
	while ((re = read(STDIN_FILENO, &tmp, 1)) > 0)
	{
		if (tmp == '\n')
			*(*lineptr + i) = '\0';
		else
			*(*lineptr + i) = tmp;
		if (*(*lineptr + i) == '\0')
		{
			*n = i;
			return (size);
		}
		i++;
		if (i >= size)
		{
			*lineptr = _realloc(*lineptr, size, size + 1);
			size++;
		}
	}
	return (-1);
}
