#include "shell.h"

/**
 * _getenv - get environment variables
 * @name: varible to find
 * @env: the whole env
 * Return: the content of the variable
 */

char *_getenv(const char *name, char **env)
{
	char **environ = env;
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

/**
 * path - get the correct path for exes
 * @av0: initial command
 * @env: the whole env
 * Return: the proper path
 */

char *path(char *av0, char **env)
{
	struct stat st;
	char *path;
	char *token, *result;
	char *delimiter = ":\n";
	char *command;
	int i = 0;
	if (stat(av0, &st) == 0)
	{
		result = str_concat(av0, "");
		return (result);
	}
	command = str_concat("/", av0);
	path = _getenv("PATH", env);
	token = strtok(path, delimiter);
	while (i < 6)
	{
		result = str_concat(token, command);
		if (stat(result, &st) == 0)
			break;
		puts("error");
		free(result);
		i++;
		token = strtok(NULL, delimiter);
	}
	free(command);
	free(path);

	if (token == NULL)
		return (NULL);
	return (result);
}
