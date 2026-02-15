#include "shell.h"

void exec_echo(Prompt);
void exec_type(Token);
void handle_type_program(Token token);

Bool execute(Prompt prompt) {
  switch (prompt.cmd.cmd) {
  case PROGRAM:
    printf("Execute %s\n", prompt.params[0].token);
    break;
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
  case PROGRAM:
    handle_type_program(token);
    break;
  case NOTFOUND:
    handle_type_program(token);
    break;
  default:
    printf("%s: not found\n", cmd.token.token);
    break;
  }
}

void handle_type_program(Token token) {
  char fullpath[250];

  if (find_exec(token, fullpath, 250)) {
    printf("%s: not found\n", token.token);
  } else {
    printf("%s is %s\n", token.token, fullpath);
  }
}
