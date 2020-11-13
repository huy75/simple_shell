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

	printf("token0: %s\n", token[0]);
	if (stat(command, &st) == -1)
	{
		free(command);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		rVal = execve(command, token, env);
	}
	else
	{
		wait(&status);
		rVal = WEXITSTATUS(status);
	}
	free(command);
	return (rVal);
}
