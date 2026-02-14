#include "shell.h"

char *get_input();
Bool prompt();
Bool execute(Prompt);
void exec_echo(Prompt);
void exec_type(Token);

int main() {
  // Flush after every printf
  setbuf(stdout, NULL);

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

Bool execute(Prompt prompt) {
  switch (prompt.cmd.cmd) {
  case ECHO:
    exec_echo(prompt);
    break;
  case EXIT:
    return FALSE;
  case TYPE:
    exec_type(prompt.params[0]);
    break;
  case NOTFOUND:
    printf("%s: command not found\n", prompt.cmd.token.token);
    break;
  }
  return TRUE;
}

void exec_echo(Prompt prompt) {
  for (int i = 0; i < prompt.params_size - 1; i++) {
    printf("%s ", prompt.params[i].token);
  }
  printf("%s\n", prompt.params[prompt.params_size - 1].token);
}

void exec_type(Token token) {
  Command cmd = get_command(token);
  switch (cmd.cmd) {
  case ECHO:
    printf("echo is a shell builtin\n");
    break;
  case EXIT:
    printf("exit is a shell builtin\n");
    break;
  case TYPE:
    printf("type is a shell builtin\n");
    break;
  case NOTFOUND:
    printf("%s: not found\n", cmd.token.token);
    break;
  }
}
