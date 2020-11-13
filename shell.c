#include "shell.h"

/**
 * main - simple shell
 * @argc: number of arguments
 * @argv: arguments
 * @env: the environ
 * Return: 0 or -1 if failed
 */
int main(int argc, char **argv, char **env)
{
	char *buffer = NULL, **token = NULL;
	int rVal;
	size_t size = 0;

	(void)argc;
	(void)argv;

	write(STDOUT_FILENO, PROMPT, sizeof(PROMPT));
	while (getline(&buffer, &size, stdin) != -1)
	{
		if (buffer[0] == EOF || checkexit(buffer) == 0)
		{
			free(buffer);
			return (0);
		}
		token = parseBuffer(buffer);
		rVal = runExec(token, env);
		printf("return value: %i\n", rVal);

		free(token);
		token = NULL;
		write(STDOUT_FILENO, PROMPT, sizeof(PROMPT));
	}

	return (rVal);
}
