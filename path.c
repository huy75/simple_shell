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
	char *path, *token, *result, *delimiter = ":\n", *command;
	char *dir = malloc(sizeof(char) * 100), current_dir[100];
	getcwd(current_dir, 100);

	if (!_strncmp(av0, "./", 2) || av0[0] == '/')
	{
		free(dir);
		if (stat(av0, &st) == 0)
		{
			result = str_concat(av0, "");
			return (result);
		}
		else
			return (NULL);
	}
	path = _getenv("PATH", env);
	token = _strtok_r(path, delimiter);
	while (token)
	{
		chdir(token);
		if (stat(av0, &st) == 0 || token[0] == '\0')
		{
			getcwd(dir, sizeof(dir));
			break;
		}
		token = _strtok_r(NULL, delimiter);
	}
	if (token == NULL)
	{
		free(path), free(dir);
		return (NULL);
	}
	command = str_concat("/", av0);
	chdir(current_dir);
	if (dir[0] == '\0' || token[0] == '\0')
		result = str_concat(current_dir, command);
	else
		result = str_concat(dir, command);
	free(command), free(dir), free(path);
	return (result);
}
