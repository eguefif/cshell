#include "shell.h"

Result get_input(char *);
bool prompt();

void run_main() {
  while (1) {
    if (prompt() == false) {
      break;
    }
  }
}

bool prompt() {
  Prompt prompt;

  printf("$ ");
  Result res = get_input(prompt.input);

  if (res == OK ) {
    parse(&prompt);
    return execute(&prompt);
  } else {
    return handle_error(res, &prompt);
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

bool handle_error(Result error, Prompt *prompt) {
  char *errno_str;

  switch (error) {
    case INPUTTOOLONG: 
      printf("Error: input is too long\n");
      break;
    case NOEOL: 
      printf("Error: no end of line\n");
      break;
    case EXECVE: 
      errno_str = strerror(errno);
      printf("Error: excve could not execute: %s\n", errno_str);
      free(errno_str);
      break;
    case CMDNOTFOUND:
      printf("%s: command not found\n", prompt->cmd.token.token);
      break;
    case CWDERROR:
      printf("%s: cwd failed\n", prompt->cmd.token.token);
      break;
    case CDPARAMS:
      printf("cd: wrong number of argument: cd PATH\n");
      break;
    case CDERROR:
      if (prompt->params_size >= 1) {
        printf("cd: %s: No such file or directory\n", prompt->params[0].token);
      } else {
        printf("cd: No such file or directory\n");
      }
      break;
    case OK:
    default:
  }
  return true;

}

Shell *get_shell() {
  static Shell shell = {0};
  return &shell;
}

void init_shell(char **env) {
  Shell *shell = get_shell();
  shell->env = env;
}

