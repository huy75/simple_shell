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
	int wc = 0;
	size_t size = 0;

	initStruct(&arguments, argc, argv, env);
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1) /* if terminal */
			_puts(PROMPT, STDOUT_FILENO);
		signal(SIGINT, sigintH); /* ignore Ctrl + C */
		if (_getline(&(arguments.buf), &size, stdin) == -1)
			break;
		if (arguments.buf[0] == EOF) /* Ctrl + D */
			break;
		if (!_strcmp(arguments.buf, "\n")) /* empty command line */
			continue;
		wc = wordCount(arguments.buf);
		if (wc == 0)
		{
			free(arguments.buf), arguments.buf = NULL;
			continue;
		}
		arguments.lCnt++;
/*              writeHist(&arguments); */
		arguments.toks = parseBuffer(arguments.buf);
/*		checkAlias(&arguments); */
		if (builtins(&arguments)) /* run built-in function */
		{
			if (runExec(&arguments)) /* exec in PATH */
			{
				errno = ENOENT; /* command not found */
				printErr(&arguments);
			}
		}
		free(arguments.buf), arguments.buf = NULL;
		free(arguments.toks), arguments.toks = NULL;
	}
	free(arguments.buf), arguments.buf = NULL;
	freeToks(&arguments), freeEnv(&arguments), freeAlias(&arguments);
	return (arguments.exitS);
}

/**
 * initStruct - initialize the argument structure
 * @args: the arguments
 * @argc: number of arguments
 * @argv: the command line
 * @env: the environ
 */
void initStruct(arguments_t *args, int argc, char **argv, char **env)
{
	if (args)
	{
		args->buf = NULL;
		args->toks = NULL;
		args->argc = argc;
		args->argv = argv[0];
		args->env = env;
		args->lCnt = 0;
		args->head_alias = NULL;
		args->head = cpyEnv(args);
		args->index = 0;
		args->exitS = 0;
/*		createHist(args); */
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

/**
 * freeToks - free all tokens
 * @args: the structure arguments
 * Return: void
 */
void freeToks(arguments_t *args)
{
	if (args->toks)
		free(*args->toks);
	free(args->toks);
	args->toks = NULL;
}

/**
 * wordCount - counts the number of words within a string.
 * @str: the input string.
 * Return: the number of words.
 */

int wordCount(char *str)
{
	int flag = 0, wc = 0;
	int idx;

	for (idx = 0; str[idx]; idx++)
		if (str[idx] == ' ')
			flag = 0;
		else if (flag == 0)
		{
			flag = 1;
			wc++;
		}
	return (wc);
}
