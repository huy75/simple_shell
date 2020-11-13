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
		command = NULL;
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
			_exit(errno);
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
 * @errVal: error value
 * @count: line count
 * Return: void
 */

void printErr(int errVal, unsigned int count)
{

}
