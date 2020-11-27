#include "shell.h"

/**
  * path2 - get the correct path for exes
  * @av0: initial command
  * @args: args
  * Return: the proper path
  */

char *path2(char *av0, arguments_t *args)
{
	struct stat st;
	char *path = NULL, *command = NULL, *token = NULL, *result = NULL;
	char *delimiter = ":\n", *pathcopy = NULL;
	int check_bin = _strcmp("/bin/", av0);

	if (_strcmp("./", av0) == 0 || _strcmp("../", av0) == 0 || check_bin == 0)
	{
		return ((stat(av0, &st) == 0) ? (str_concat(av0, "")) : NULL);
	}
	pathcopy = _getenvLL2("PATH", args);
	if (pathcopy == NULL)
	{
		errno = ENOENT;
		return (NULL);
	}
	path = str_concat(pathcopy, ""), token = _strtok_r(path, delimiter);
	while (token)
	{
		if (_strcmp(token, av0) == 0 && stat(av0, &st) == 0)
		{
			result = str_concat(av0, "");
			break;
		}
		if (stat(av0, &st) == 0 && _strcmp(token, "") == 0)
		{
			result = str_concat(av0, "");
			break;
		}
		command = str_concat("/", av0), result = str_concat(token, command);
		if (stat(result, &st) == 0)
		{
			free(command);
			break;
		}
		free(result), free(command), token = _strtok_r(NULL, delimiter);
	}
	free(path);
	if (token == NULL)
		return (NULL);
	return (result);
}
