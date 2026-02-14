#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_input() {
  char *input = (char *)malloc(1000);

  fgets(input, 1000, stdin);

  int len = strlen(input);
  for (int i = 0; i < len; i++) {
    if (input[i] == '\n') {
      input[i] = '\0';
      break;
    }
  }

  return input;
}

int prompt() {
  printf("$ ");
  char *input = get_input();
  if (strncmp(input, "exit", 50) == 0) {
    return 0;
  }
  printf("%s: command not found\n", input);
  return 1;
}

int main() {
  // Flush after every printf
  setbuf(stdout, NULL);

  while (1) {
    if (prompt() == 0) {
      break;
    }
  }

  return 0;
}
