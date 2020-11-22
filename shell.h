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
#define PRSIZE _strlen(PROMPT)
#define TOKENBUF 5

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

/**
 * struct arguments - for various functions
 * @buf: input command
 * @toks: array of strings
 * @argc: argument count
 * @argv: argv
 * @env: env
 * @lCnt: line count
 * @head: first node
 * @index: to delete node
 * @exitS: exit status
 */
typedef struct arguments
{
	char *buf;
	char **toks;
	int argc;
	char *argv;
	char **env;
	int lCnt;
	list_t *head;
	int index;
	int exitS;
} arguments_t;

/**
 * struct builtins_s - struct for builtins
 * @cmd: command
 * @bfc: built-in function
 */
typedef struct builtins_s
{
	char *cmd;
	int (*bfc)(arguments_t *args);
} builtins_t;

/* shell.c module */
int main(int argc, char **argv, char **env);
void initStruct(arguments_t *args, int argc, char **argv, char **env);
void sigintH(int signum);
void freeToks(arguments_t *args);

/* parse.c module */
char **parseBuffer(char *buffer);

/* path.c module */
char *_getenv(const char *name, char **env);
char *path(char *av0, char **env);
int scan_path_vars(char *path);

/* fork.c module */
int runExec(arguments_t *args);
void printErr(arguments_t *args);

/* _realloc.c module */
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* _getline.c module */
char *_strcpy(char *dest, char *src);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* _strtok.c module */
char get_del(char *str, const char *delim);
char *_strtok(char *str, const char *delim);

/* strings.c module */
int _putchar(char c, int fd);
void _puts(char *str, int fd);
unsigned int _strlen(const char *s);
char *str_concat(char *s1, char *s2);
void print_number(int n);

/* strings2.c module */
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strstr(char *haystack, char *needle);
int _atoi(char *s);
char *_strchr(char *s, char c);

/* strings3.c module */
char *_strdup(char *str);
char *_strcat(char *dest, char *src);

/* builtins.c module */
int builtins(arguments_t *args);
int _bEnv(arguments_t *args);
int _bExit(arguments_t *args);
int _bSEnv(arguments_t *args);
int _bUEnv(arguments_t *args);

/* builtins2.c module */
int _bHelp(arguments_t *args);

/* help.c module */
void helpEnv(void);
void helpSEnv(void);
void helpUEnv(void);

/* environment.c module */
list_t *cpyEnv(arguments_t *args);
list_t *add_node_end(list_t **head, char *str);
list_t *_getenvLL(char *name, arguments_t *args);
int delete_node_at_index(list_t **head, unsigned int index);
void freeEnv(arguments_t *args);

#endif /* __SHELL__ */
