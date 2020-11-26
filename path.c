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
	char *result = NULL;

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
 * scan_path_vars - checks whether path contains a "::"
 * before /bin/ or a ":" at path[0]
 * @path: the entire path
 * Return: 1 if any is true or 0 otherwise
 */

int scan_path_vars(char *path)
{
	char *binloc, *emptyloc;
	int lenB, lenE, lenP;

	if (path[0] == ':')
		return (1);
	if (path[0] == '/' && path[1] == 'b')
		return (0);
	lenP = _strlen(path);
	if (path[lenP] == ':' || path[lenP - 1] == ':')
		return (1);
	binloc = _strstr(path, ":/bin");
	emptyloc = _strstr(path, "::");
	if (binloc != NULL && emptyloc != NULL)
	{
		lenB = _strlen(binloc);
		lenE = _strlen(emptyloc);
		if (lenE > lenB)
			return (1);
	}
	return (0);
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

	if (stat(av0, &st) == 0)
	{
		result = str_concat(av0, "");
		return (result);
	}
	command = str_concat("/", av0);
	path = _getenv("PATH", env);
	if (scan_path_vars(path) == 1 && stat(av0, &st) == 0)
		return (str_concat(av0, ""));
	token = _strtok(path, delimiter);
	while (token)
	{
		result = str_concat(token, command);
		if (stat(result, &st) == 0)
			break;
		free(result);
		token = _strtok(NULL, delimiter);
	}
	free(command);
	free(path);

	if (token == NULL)
		return (NULL);
	return (result);
}
