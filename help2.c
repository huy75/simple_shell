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
	_puts("    - 'cd -' will get back to the previous directory.\n", STDIN_FILENO);
	_puts("    - the environment variable $PWD is updated.\n", STDIN_FILENO);
}

/**
 * helpHist - prints help info for history built-in
 * Return: void
 */
void helpHist(void)
{
	_puts("history\n", STDIN_FILENO);
        _puts("    - [line number] the history list\n", STDIN_FILENO);
}
