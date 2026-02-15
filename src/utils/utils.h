#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "../parser/parser.h"

// String utils
bool is_whitespace(char);
char *strdeepcopy(char *source);
char *trim_start(char *str);

// File utils
bool is_exec_exist(char*);
bool find_exec(char *, char *, size_t);
#endif
