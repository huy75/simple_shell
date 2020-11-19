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
	int rVal, lineCount = 0;
	size_t size = 0;

	initStruct(&arguments);
	arguments.argc = argc;
        arguments.argv = argv[0];

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			_puts(PROMPT, 1);
		if (getline(&(arguments.buf), &size, stdin) != -1)
		{
			if (_strcmp(arguments.buf, "\n") != 0)
			{
				if (arguments.buf[0] == EOF)
				{
					free(arguments.buf);
					return (0);
				}
				arguments.toks = parseBuffer(arguments.buf);
				rVal = builtins(&arguments);
				if (rVal)
				{
					rVal = runExec(arguments.toks, env);

					arguments.lCnt++;
					if (rVal)
						printErr(&arguments);
				}
				free(arguments.toks);
				arguments.toks = NULL;
			}
		}
		else
		{
			free(arguments.buf);
			arguments.buf = NULL;
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
		args->toks = NULL;
		args->argv = NULL;
		args->argc = 0;
		args->lCnt = 0;
	}
}
