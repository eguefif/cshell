#include "shell.h"

void exec_echo(Prompt);
void exec_type(Token);
void handle_type_program(Token token);

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
  case PROGRAM:
    printf("Execute %s\n", prompt.params[0].token);
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
  default:
    printf("%s: not found\n", cmd.token.token);
    break;
  }
}

void handle_type_program(Token token) {
  // look into the PATH env for a list of paths
  // then check where is the program
}
