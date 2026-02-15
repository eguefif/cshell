#include "shell.h"

size_t find_first_whitespace(char *str) {
  size_t cursor = 0;

  while (str[cursor] != '\0' && !is_whitespace(str[cursor])) {
    cursor++;
  }
  return cursor;
}

char *trim_start(char *str) {
  size_t index = find_first_whitespace(str);
  size_t cursor = 0;
  while (str[index] != '\0') {
    str[cursor] = str[index];
    index++;
    cursor++;
  }
  return str;
}

bool is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

// Allocate and copy a string
// The pointer that is returned must be freed manually
char *strdeepcopy(char *source) {
  size_t target_size = strlen(source) + 1;
  char *target = malloc(target_size);
  target[strlen(source)] = '\0';
  // SAFETY: It is safe as we created a buffer big enough
  // from the source size
  memcpy(target, source, target_size);
  return target;
}
