#include "shell.h"

/**
 * runExec - run the executable
 * @token: the command in full
 * @env: environ
 * Return: return 0 if success
 */
int runExec(char **token, char **env)
{
	int status;
	pid_t pid;
	char *command = path(token[0], env);

	if (command == NULL)
		return (EXIT_FAILURE);

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
			_exit(0);
		}
	}
	else
	{
		if (wait(&status) == -1)
			perror("wait");
/*		if (WIFEXITED(status))
		rVal = WEXITSTATUS(status); */
	}
	free(command);
	command = NULL;
	return (0);
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

	switch (errno)
	{
	case ENOENT:
		_puts(args->toks[0], STDERR_FILENO);
		_puts(": not found\n", STDERR_FILENO);
		args->exitS = 127;
		break;
	case EINVAL:
		_puts(args->toks[0], STDERR_FILENO);
		_puts(": Illegal number: ", STDERR_FILENO);
		_puts(args->toks[1], STDERR_FILENO);
		_puts("\n", STDERR_FILENO);
		args->exitS = 128;
		break;
	}
}
