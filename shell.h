#ifndef __SHELL__
#define __SHELL__
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>

#define BUFSIZE 1024
#define ENV extern char **environ
#define PROMPT "$ "

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

char *_getenv(const char *name);
list_t *add_node_end(list_t **head, const char *str);

#endif /* __SHELL__ */
