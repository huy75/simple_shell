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
	_puts("    - If the variable [name] does exist", STDIN_FILENO);
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
	_puts("    - If [name] does not exist", STDIN_FILENO);
	_puts(" the environment is unchanged.\n", STDIN_FILENO);
}
