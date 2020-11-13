#ifndef __SHELL__
#define __SHELL__

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>


#define BUFSIZE 1024
#define DELIMITERS " \t\r\n\v\f"
#define ENV extern char **environ
#define PROMPT "> "

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

/* fork.c module */
int runExec(char **token, char **env);

/* parse.c */
char **parseBuffer(char *buffer);
void freeToken(char **token);

/* path.c module */
unsigned int _strlen(const char *s);
char *str_concat(char *s1, char *s2);
char *_getenv(const char *name);
char *path(char *av0);

/* _realloc.c module */
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif /* __SHELL__ */
