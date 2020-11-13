#include "shell.h"

/**
 * _exit - check if input = exit
 * @command: the input
 * Return: -1 if false, 0 otherwise
 */

int checkexit(char *command)
{
	char *exit = "exit";
	unsigned int i = 0;

	while(command[i])
	{
		if (command[i] != exit[i])
			break;
		i++;
	}
	if (i != 4)
		return (-1);
	return (0);
}
