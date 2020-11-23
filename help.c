#include "shell.h"

/**
 * helpEnv - prints help info for env built-in
 * Return: void
 */
void helpEnv(void)
{
	_puts("env\n"
	      "    Prints the environment variables.\n", STDIN_FILENO);
}

/**
 * helpSEnv - prints help info for setenv built-in
 * Return: void
 */
void helpSEnv(void)
{
	_puts("setenv [name] [value]\n", STDIN_FILENO);
	_puts("    - adds the variable [name] ", STDIN_FILENO);
	_puts("to the environment with the [value].\n", STDIN_FILENO);
	_puts("    - if the variable [name] does exist", STDIN_FILENO);
	_puts(" its value is overwritten by [value].\n", STDIN_FILENO);
}

/**
 * helpUEnv - prints help info for setenv built-in
 * Return: void
 */
void helpUEnv(void)
{
	_puts("unsetenv [name]\n", STDIN_FILENO);
	_puts("    - deletes the variable [name] ", STDIN_FILENO);
	_puts("from the environment.\n", STDIN_FILENO);
	_puts("    - if [name] does not exist", STDIN_FILENO);
	_puts(" the environment is unchanged.\n", STDIN_FILENO);
}

/**
 * helpHelp - prints help info for help built-in
 * Return: void
 */
void helpHelp(void)
{
	_puts("help [command]\n", STDIN_FILENO);
	_puts("    - if specified, displays help on [command].\n", STDIN_FILENO);
	_puts("    - displays brief summaries of all commands.\n", STDIN_FILENO);
}

/**
 * helpExit - prints help info for exit built-in
 * Return: void
 */
void helpExit(void)
{
	_puts("exit [n]\n", STDIN_FILENO);
	_puts("    - exits the Shell with status [N], ", STDIN_FILENO);
	_puts("if [N] is specified.\n", STDIN_FILENO);
	_puts("    - if not, with the status of the last command.\n", STDIN_FILENO);
}
