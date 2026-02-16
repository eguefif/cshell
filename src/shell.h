#ifndef SHELL_H
#define SHELL_H

#define PROMPT_MAX_SIZE 150
#define MAX_SIZE_PATH 1000
#define MAX_PARAMS 150

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "./arena/arena.h"

typedef struct myShell{
  char **env;
} Shell;

void run_main();

Shell *get_shell();
void init_shell(char **env);

#endif
