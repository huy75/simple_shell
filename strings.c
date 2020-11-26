#include "shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * @fd: file descriptor
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c, int fd)
{
	return (write(fd, &c, 1));
}

/**
 *_puts - prints a string, followed by a new line, to stdout.
 * @str: the input string
 * @fd: file descriptor
 * Return: nothing to return.
 */
void _puts(char *str, int fd)
{
	while (*str != 0)
	{
		_putchar(*str, fd);
		str++;
	}
}

/**
 * _strlen - the length of a string
 * @s: the string
 * Return: the lenght of the string
 */

unsigned int _strlen(const char *s)
{
	unsigned int result = 0;

	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		result++;
		s++;
	}
	return (result);
}

/**
 * str_concat - concatenates two strings
 * @s1: 1st string
 * @s2: 2nd string
 *
 * Return: point to mem address where the result is stored
 * NULL on failure or empty string if NULL is passed
 */

char *str_concat(char *s1, char *s2)
{
	unsigned int len_s1 = _strlen(s1);
	unsigned int len_s2 = _strlen(s2);
	char *ar = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	unsigned int i;

	if (ar == NULL)
		return (NULL);
	for (i = 0; i < len_s1; i++)
		ar[i] = s1[i];
	for (i = 0; i < len_s2; i++)
		ar[i + len_s1] = s2[i];
	ar[len_s1 + len_s2] = '\0';
	return (ar);
}

/**
 * print_number - prints a number with only _putchar,
  * @n: number to be printed.
 * Return: void.
 */

void print_number(int n)
{
	int p, nb;

	p = 1;
	while (n / p >= 10 || n / p <= -10)
		p *= 10;

	while (p)
	{
		nb = n / p;
		if (nb < 0)
		{
			_putchar('-', 2);
			_putchar('0' - nb, 2);
			n = -(n - nb * p);
		}
		else
		{
			_putchar('0' + nb, 2);
			n = n - nb * p;
		}
		p /= 10;
	}
}
