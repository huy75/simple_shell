#include "shell.h"

/**
 * runExec - run the executable
 * @token: the command in full
 * @env: environ
 * Return: return value 127 if file not found, or from system call / macro
 */
int runExec(char **token, char **env)
{
	int rVal, status;
	pid_t pid;
	struct stat st;
	char *command = path(token[0], env);

	if (stat(command, &st) == -1)
	{
		printf("command not found\n");
/*		free(command);
 */
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		rVal = execve(command, token, env);
		if (rVal == -1)
		{
			free(command);
			command = NULL;
			perror("execve");
			exit(errno);
		}
	}
	else
	{
		if (wait(&status) == -1)
			perror("wait");
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		wait(&status);
		rVal = status;
	}
	free(command);
	command = NULL;
	return (rVal);
}

/**
 * printErr - prints error message
 * @token: the command in full
 * @av: shell name
 * @errVal: error value
 * @count: line count
 * Return: void
 */
void printErr(char **token, char **av, int errVal, unsigned int count)
{
	if (errVal == 127)
	{
		_puts(av[0]);
		_puts(": ");
		print_number(count);
		_puts(": ");
		_puts(token[0]);
		_puts(": not found\n");
	}
}
