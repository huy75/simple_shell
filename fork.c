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
	char *command = path(token[0], env);

	if (command == NULL)
		return (127);
	pid = fork();
	if (pid == -1)
	{
		free(command);
		command = NULL;
		perror("fork");
		exit(errno);
	}
	if (pid == 0)
	{
		if (execve(command, token, env) == -1)
		{
			free(command);
			command = NULL;
			_exit(127);
		}
	}
	else
	{
		if (wait(&status) == -1)
			perror("wait");
		if (WIFEXITED(status))
			rVal = WEXITSTATUS(status);
	}
	free(command);
	command = NULL;
	return (rVal);
}

/**
 * printErr - prints error message
 * @args: args
 * Return: void
 */
void printErr(arguments_t *args)
{
	_puts(args->argv, STDERR_FILENO);
	_puts(": ", STDERR_FILENO);
	print_number(args->lCnt);
	_puts(": ", STDERR_FILENO);
	_puts(args->toks[0], STDERR_FILENO);
	_puts(": not found\n", STDERR_FILENO);
}
