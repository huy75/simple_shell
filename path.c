#include "shell.h"

/**
* _strlen - the length of a string
* @s: the string
*
* Return: the lenght of the string
*/

unsigned int _strlen(const char *s)
{
	unsigned int result = 0;

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

char *_getenv(const char *name)
{
	extern char **environ;
	unsigned int size, a, j, i = 0;
	char *result;

	while (environ[i] != NULL)
	{
		j = 0;
		while (name[j] != '\0')
		{
			if (name[j] != environ[i][j])
				break;
			j++;
		}
		if (j == _strlen(name))
		{
			j++;
			a = 0;
			size = _strlen(environ[i]) - _strlen(name) + 1;
			result = malloc(sizeof(char) * size);
			if (result == NULL)
				return (NULL);
			while (environ[i][j] != '\0')
			{
				result[a] = environ[i][j];
				j++, a++;
			}
			break;
		}
		i++;
	}
	if (environ[i] == NULL)
		return (NULL);
	return (result);
}

char *path(char *av0)
{
	struct stat st;
	char *path;
	char *token, *result;
	char *delimiter = ":\n";
	char *command;

	if (stat(av0, &st) == 0)
		return (av0);

	command = str_concat("/", av0);
	path = _getenv("PATH");
	token = strtok(path, delimiter);
	while (token)
	{
		result = str_concat(token, command);
		if (stat(result, &st) == 0)
			break;
		free(result);
		token = strtok(NULL, delimiter);
	}
	if (token == NULL)
		perror("./hsh");

	free(command);
	free(path);
	return (result);
}

int main(void)
{
	char *test1;
	char *test2;

	test1 = path("/bin/ls");
	printf("Test1: %s\n", test1);
	test2 = path("ls");
	printf("Test2: %s\n", test2);
	free(test2);
	return (0);
}