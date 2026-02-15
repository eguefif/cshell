#include "shell.h"

int find_first_whitespace(char *str) {
  int cursor = 0;

  while (str[cursor] != '\0' && !is_whitespace(str[cursor])) {
    cursor++;
  }
  return cursor;
}

char *trim_start(char *str) {
  int index = find_first_whitespace(str);
  int cursor = 0;
  while (str[index] != '\0') {
    str[cursor] = str[index];
    index++;
    cursor++;
  }
  return str;
}

Bool is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

// Allocate and copy a string
// The pointer that is returned must be freed manually
char *strdeepcopy(char *source) {
  char *target = malloc(strlen(source) + 1);
  target[strlen(source)] = '\0';
  strncpy(target, source, strlen(source));
  return target;
}
