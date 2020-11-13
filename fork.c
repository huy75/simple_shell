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

	printf("token0: %s\n", token[0]);
	if (stat(token[0], &st) == -1)
		return (127);

	pid = fork();
	if (pid == 0)
	{
		rVal = execve(token[0], token, env);
	}
	else
	{
		wait(&status);
		rVal = WEXITSTATUS(status);
	}
	return (rVal);
}
