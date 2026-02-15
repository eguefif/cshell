#include "shell.h"

Result get_input(char *);
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
  Result res = get_input(prompt.input);
  if (res == OK ) {
    parse(&prompt);
    return execute(prompt);
  } else {
    return handle_error(res);
  }
}

Result get_input(char *input) {
  // Refactor, this value is arbitrary

  fgets(input, PROMPT_MAX_SIZE, stdin);

  size_t len = strlen(input);
  for (size_t i = 0; i < len; i++) {
    if (input[i] == '\n') {
      input[i] = '\0';
      return OK;
    }
  }
  return INPUTTOOLONG;
}

bool handle_error(Result error) {
  switch (error) {
    case INPUTTOOLONG: printf("Error: input is too long\n");
                       break;
    case NOEOL: printf("Error: no end of line\n");
    case OK:
    default:
  }
  return true;

}
