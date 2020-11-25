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
	char *path, *command, *token, *result;
	char *delimiter = ":\n";

	if (_strcmp("./", av0) == 0)
	{
		if (stat(av0, &st) == 0)
			return (str_concat(av0, ""));
		else
			return (NULL);
	}

	path = _getenv("PATH", args->env);
	token = _strtok_r(path, delimiter);
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
		command = str_concat("/", av0);
		result = str_concat(token, command);
		if (stat(result, &st) == 0)
			break;
		free(result), free(command);
		token = _strtok_r(NULL, delimiter);
	}
	free(path);
	if (token == NULL)
		return (NULL);
	return (result);
}