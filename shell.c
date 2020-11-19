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
	arguments_t arguments;
	char *buffer = NULL, **token = NULL;
	int rVal, lineCount = 0;
	size_t size = 0;

	initStruct(&arguments);
	arguments.ac = argc;
        arguments.argv = argv[0];

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			_puts(PROMPT, 1);
		if (getline(&buffer, &size, stdin) != -1)
		{
			if (_strcmp(buffer, "\n") != 0)
			{
				if (buffer[0] == EOF || checkexit(buffer) == 0)
				{
					free(buffer);
					return (0);
				}
				token = parseBuffer(buffer);
				arguments.arr = token;
				rVal = builtins(&arguments);
				printf("rVal: %i\n", rVal);
				if (rVal)
				{
					rVal = runExec(token, env);

					lineCount++;
					if (rVal)
						printErr(token, argv, rVal, lineCount);
				}
				free(token);
				token = NULL;
			}
		}
		else
		{
			free(buffer);
			buffer = NULL;
			break;
		}
	}

	return (rVal);
}

/**
 * initStruct - initialize the argument structure
 * @args: args
 */
void initStruct(arguments_t *args)
{

	if (args)
	{
		args->buf = NULL;
		args->arr = NULL;
		args->argv = NULL;
		args->ac = 0;
		args->exit_status = 0;
	}
}
