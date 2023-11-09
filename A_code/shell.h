#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define DELIM " \n\t"


extern char **environ;

char *read_line(void);
char **tokenizer(char *line);
int _execute(char **command, char **argv, int idx);
char *_getenv(char *variable);
char *_getpath(char *command);


char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
int _strlen(char *s);

void freearray2D(char **arr);
void reverse_string(char *str, int len);
char *_itoa(int n);
void print_error(char *name, char *cmd, int idx);


#endif

