#include "shell.h"

// TODO: replace all int related to a size by size_t
// TODO: handle error

void get_input(char *);
bool prompt();

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
    printf("Usage: %s\n", argv[0]);
    exit(0);
  }
  init_shell(env);

  while (1) {
    if (prompt() == false) {
      break;
    }
  }

  return 0;
}

bool prompt() {
  Prompt prompt;
  printf("$ ");
  get_input(prompt.input);
  parse(&prompt);
  return execute(prompt);
}

void get_input(char *input) {
  // Refactor, this value is arbitrary

  fgets(input, PROMPT_MAX_SIZE, stdin);

  int len = strlen(input);
  // TODO: Handle error when no \n because prompt is too big
  for (int i = 0; i < len; i++) {
    if (input[i] == '\n') {
      input[i] = '\0';
      break;
    }
  }
}
