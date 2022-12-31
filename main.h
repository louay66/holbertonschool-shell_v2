#define _GNU_SOURCE
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <time.h>
extern char **environ;

char *read_line(void);
char **split_line(char *line);
int execute_command(char **args);
int execute_builtin_command(char **args);
int execute(char **args);
char *_memcpy(char *dest, char *src, unsigned int n);
int _strcmp(char *s1, char *s2);
void *my_realloc(void *ptr, size_t new_size);

#endif
