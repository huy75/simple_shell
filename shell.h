#ifndef __SHELL__
#define __SHELL__

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>

#define BUFSIZE 1024
#define ENV extern char **environ
#define PROMPT "$ "

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @next: points to the next node
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

#endif /* __SHELL__ */
