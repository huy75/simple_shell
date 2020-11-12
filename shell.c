#include "shell.h"

/**
 * main - simple shell
 * Return: 0 or 98 if failed
 */
int main(void)
{
	char *av[1024], *buffer, *token;
	char delimiters[] = " \t\r\n\v\f";
	size_t size = BUFSIZE;
	int status, idx;
	pid_t pid;

	buffer = malloc(sizeof(char) * BUFSIZE);
        if (!buffer)
                perror("ERROR: Unable to allocate buffer\n"), exit(98);

	while (1)
	{
		write(STDOUT_FILENO, PROMPT, sizeof(PROMPT));
		if (getline(&buffer, &size, stdin) == -1)
			return (1);

		token = strtok(buffer, delimiters);

		for (idx = 0; token; idx++)
		{
			av[idx] = token;
			token = strtok(NULL, delimiters);
		}
		av[idx] = NULL;

		pid = fork();
		if (pid == 0)
		{
			if (execve(av[0], av, NULL) == -1)
				perror("sh");
		}
		else
			wait(&status);
	}
	free(buffer);
	return (0);
}
