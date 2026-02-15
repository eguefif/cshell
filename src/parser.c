#include "shell.h"

Command get_command(Token token) {
  Command cmd = {NOTFOUND, token};

  if (strncmp(token.token, "exit", 4) == 0) {
    cmd.cmd = EXIT;
  } else if (strncmp(token.token, "echo", 4) == 0) {
    cmd.cmd = ECHO;
  } else if (strncmp(token.token, "type", 4) == 0) {
    cmd.cmd = TYPE;
  } else if (token.type == STRING) {
    cmd.cmd = PROGRAM;
  }

  return cmd;
}

Prompt parse(char *input) {
  Token *tokens = tokenize(input);
  int count = 1;
  Command cmd = get_command(tokens[0]);
  Token *params = (Token *)malloc(sizeof(Token) * 100);

  while (1) {
    if (tokens[count].type == EOP) {
      break;
    }
    params[count - 1] = tokens[count];
    count++;
  }

  Prompt p = {cmd, params, count - 1};

  free(tokens);
  return p;
}
