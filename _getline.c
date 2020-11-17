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
	char buf[1024];
	char *tmp;
	unsigned int len;
	int i = 0;

	(void)stream;

	read(STDIN_FILENO, buf, sizeof(buf));

	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			break;
		}
		i++;
	}
	len = _strlen(buf);
	tmp = _realloc(*lineptr, sizeof(lineptr), 1024);
	if (tmp == NULL)
		return (-1);
	*lineptr = tmp;
	*n = 1024;

	_strcpy(*lineptr, buf);
	return (len);
}
