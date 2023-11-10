#ifndef _A_SHELL_H_
#define _A_SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER 1024
#define MAX_WORDS 100
#define MAX_PATH_LENGTH 1024
extern char **environ;

/* prompt function */
int _prompt(char **line, size_t *len, char *prompt);

/* string helper functions */
int _strlen(char *s);
size_t _strcspn(const char *s, const char *reject);
char *_strdup(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);

/* execution helper functions */
char **tokenise(char *input, const char *e_str);
void exec(char **argv);

/* free functions */
void freesplit(char **split);

/* environment helper functions */
char *_getenv(const char *name);
char *_which(char *filename);
int starts_with(const char *s, const char *prefix);
int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);

/* structure for a single node in linked list */
typedef struct PathNode
{
	char *directory;
	struct PathNode *next;
} PathNode;

/* linked list functions */
PathNode *add_PathNode_end(PathNode *head, char *dir);
PathNode *get_PathList(void);
void freelist(PathNode *head);

#endif /* _A_SHELL_H_ */
