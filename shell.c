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
	int rVal;
	size_t size = 0;

	initStruct(&arguments, env);
	arguments.argc = argc;
        arguments.argv = argv[0];

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			_puts(PROMPT, 1);
		signal(SIGINT, sigintH);
		if (_getline(&(arguments.buf), &size, stdin) != -1)
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
void initStruct(arguments_t *args, char **env)
{

	if (args)
	{
		args->buf = NULL;
		args->toks = NULL;
		args->argv = NULL;
		args->argc = 0;
		args->env = env;
		args->lCnt = 0;
		args->head = cpyEnv(args);
		args->index = 0;
		args->exitS = 0;
	}
}

/**
 * sigintH - handles SIGINT (CTRL-C)
 * @signum: signal number caught by signal, 2 for SIGINT
 **/
void sigintH(int signum)
{
	if (signum == 2)
	{
		_putchar('\n', 1);
		_puts(PROMPT, 1);
	}
}
