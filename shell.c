#include "shell.h"

/**
 * main - simple shell
 * @argc: number of arguments
 * @argv: arguments
 * @env: the environ
 * Return: 0
 */
int main(int argc, char **argv, char **env)
{
	arguments_t arguments;
	size_t size = 0;

	initStruct(&arguments, env);
	arguments.argc = argc;
	arguments.argv = argv[0];
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1) /* if terminal */
			_puts(PROMPT, STDOUT_FILENO);
		signal(SIGINT, sigintH); /* ignore Ctrl + C */
		if (_getline(&(arguments.buf), &size, stdin) == -1)
		{
			free(arguments.buf);
			arguments.buf = NULL;
			break;
		}
		if (!_strcmp(arguments.buf, "\n")) /* empty command line */
			continue;
		if (arguments.buf[0] == EOF) /* Ctrl + D */
		{
			free(arguments.buf);
			return (EXIT_SUCCESS);
		}
		arguments.lCnt++;
		arguments.toks = parseBuffer(arguments.buf);
		if (builtins(&arguments)) /* not a built-in function */
		{
			if (runExec(arguments.toks, env)) /* exec in PATH */
				printErr(&arguments);
			free(arguments.toks);
			arguments.toks = NULL;
		}
	}
	return (0);
}

/**
 * initStruct - initialize the argument structure
 * @args: the arguments
 * @env: the environ
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
 * Return : void
 **/
void sigintH(int signum)
{
	if (signum == SIGINT)
	{
		_putchar('\n', STDOUT_FILENO);
		_puts(PROMPT, STDOUT_FILENO);
	}
}
