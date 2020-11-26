#include "shell.h"

/**
 * createHist - creates a history file.
 * @args: arguments
 * Return: EXIT
 */
int createHist(arguments_t *args)
{
	char *envH = NULL, *fileN = NULL;
	int fd;
	struct stat st;

	envH = _getenvVAL("HOME", args);

	fileN = malloc(_strlen(envH) + _strlen(HISTORY) + 2);
	if (!fileN)
	{
		free(envH);
		return (EXIT_FAILURE);
	}
	_strcpy(fileN, envH), _strcat(fileN, "/"), _strcat(fileN, HISTORY);
	if (stat(fileN, &st) != 0)
	{
		fd = open(fileN, O_RDWR | O_CREAT | O_TRUNC, 0600);
		if (fd == -1)
		{
			free(envH);
			free(fileN);
			return (EXIT_FAILURE);
		}
		close(fd);
	}
	free(envH);
	free(fileN);
	return (EXIT_SUCCESS);
}


/**
 * writeHist - writes input command to history file
 * @args: arguments structure
 * Return: int.
 */
int writeHist(arguments_t *args)
{
	char *envH = NULL, *fileN = NULL;
	int bytes, fd;

	envH = _getenv("HOME", args->env);

	fileN = malloc(_strlen(envH) + _strlen(HISTORY) + 2);
	if (!fileN)
	{
		free(envH);
		return (EXIT_FAILURE);
	}
	_strcpy(fileN, envH), _strcat(fileN, "/"), _strcat(fileN, HISTORY);
	fd = open(fileN, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		free(envH);
		free(fileN);
		return (EXIT_FAILURE);
	}
	bytes = write(fd, args->buf, _strlen(args->buf));
	if (bytes == -1)
	{
		free(envH);
		free(fileN);
		close(fd);
		return (EXIT_FAILURE);
	}
	write(fd, "\n", 1);
	free(envH);
	free(fileN);
	close(fd);
	return (EXIT_SUCCESS);
}
