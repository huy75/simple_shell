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

#define DELIMITERS " \t\r\n\v\f"
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
void printErr(char **token, char **argv, int errVal, unsigned int count);

/* parse.c */
char **parseBuffer(char *buffer);

/* path.c module */
char *_getenv(const char *name, char **env);
char *path(char *av0, char **env);

/* strings.c module */
int _putchar(char c);
void _puts(char *str);
unsigned int _strlen(const char *s);
char *str_concat(char *s1, char *s2);
void print_number(int n);

/* _realloc.c module */
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* _exit.c module */
int checkexit(char *command);

#endif /* __SHELL__ */
