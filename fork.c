#include "shell.h"

/**
 * runExec - run the executable
 * @args: the arguments
 * Return: return 0 if success
 */
int runExec(arguments_t *args)
{
	int status;
	pid_t pid;
	char *command = path2(args->toks[0], args);

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
		if (execve(command, args->toks, args->env) == -1)
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
		if (WIFEXITED(status))
			args->exitS = WEXITSTATUS(status);
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
	case EXITERR:
		_puts(args->toks[0], STDERR_FILENO);
		_puts(": Illegal number: ", STDERR_FILENO);
		_puts(args->toks[1], STDERR_FILENO);
		_puts("\n", STDERR_FILENO);
		args->exitS = 2;
		break;
	case EINVAL:
		_puts(args->toks[0], STDERR_FILENO);
		_puts(": invalid argument(s)\n", STDERR_FILENO);
		args->exitS = 0;
		break;
	case ENOTDIR:
		_puts(args->toks[0], STDERR_FILENO);
		_puts(": can't cd to ", STDERR_FILENO);
		_puts(args->toks[1], STDERR_FILENO);
		_putchar('\n', STDERR_FILENO);
		args->exitS = 2;
		break;
	}
}
