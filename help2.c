#include "shell.h"

/**
 * helpCd - prints help info for cd built-in
 * Return: void
 */
void helpCd(void)
{
	_puts("cd [directory]\n", STDIN_FILENO);
	_puts("    - changes to [directory]\n", STDIN_FILENO);
	_puts("    - if no argument is given, ", STDIN_FILENO);
	_puts("the command must be interpreted like cd $HOME.\n", STDIN_FILENO);
	_puts("    - 'cd -' will get back to the previous directory.\n", 1);
	_puts("    - the environment variable $PWD is updated.\n", 1);
}

/**
 * helpAlias - prints help info for alias built-in
 * Return: void
 */
void helpAlias(void)
{
	_puts("alias\n", STDIN_FILENO);
	_puts("    - prints a list of all aliases\n", STDIN_FILENO);
	_puts("alias [name]=[value]\n", STDIN_FILENO);
	_puts("    - defines or replaces an alias for the given value\n", 1);
}

/**
 * helpHist - prints help info for history built-in
 * Return: void
 */
void helpHist(void)
{
	_puts("history\n", STDIN_FILENO);
	_puts("    - prints the history list, one command by line, ", 1);
	_puts("preceded with line numbers (starting at 0).\n", STDIN_FILENO);
}
