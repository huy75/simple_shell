#include "shell.h"

/**
  * _getenvVAL - gets the actual value of env var
  * @var: name of variable
  * @args: args
  * Return: a string or NULL if found nothing
  */

char *_getenvVAL(char *var, arguments_t *args)
{
	char *wholeV = (_getenvLL(var, args))->str;
	char *token = NULL;
	int i = 0;

	if (wholeV == NULL)
		return (NULL);
	while (wholeV[i] != '=')
		i++;
	i++;
	token = wholeV + i;
	return (token);
}
