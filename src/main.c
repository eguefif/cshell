#include "shell.h"

char *get_input();
Bool prompt();

Shell *get_shell() {
  static Shell shell = {0};
  return &shell;
}

void init_shell(char **env) {
  Shell *shell = get_shell();
  shell->env = env;
}

int main(int argc, char **argv, char **env) {
  // Flush after every printf
  setbuf(stdout, NULL);
  if (argc > 1) {
    printf("Usafe: %s\n", argv[0]);
    exit(0);
  }
  init_shell(env);

  while (1) {
    if (prompt() == FALSE) {
      break;
    }
  }

  return 0;
}

char *get_input() {
  // Refactor, this value is arbitrary
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

Bool prompt() {
  printf("$ ");
  char *input = get_input();
  Prompt prompt = parse(input);
  int retval = execute(prompt);
  free(input);
  return retval;
}
