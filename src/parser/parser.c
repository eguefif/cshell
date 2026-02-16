#include "./parser.h"

Command get_command(Token);

void parse(Prompt *prompt) {
  Token *tokens = tokenize(prompt->input);
  Command cmd = get_command(tokens[0]);

  int i = 0;
  while (tokens[i].type != EOP) {
    prompt->params[i] = tokens[i];
    i++;
  }
  prompt->params_size = i;
  prompt->cmd = cmd;
}

Command get_command(Token token) {
  Command cmd = {NOTFOUND, token};

  if (strncmp(token.token, "exit", MIN(token.size, 4)) == 0) {
    cmd.cmd = EXIT;
  } else if (strncmp(token.token, "echo", MIN(token.size, 4)) == 0) {
    cmd.cmd = ECHO;
  } else if (strncmp(token.token, "pwd", MIN(token.size,3)) == 0) {
    cmd.cmd = PWD;
  } else if (strncmp(token.token, "type", MIN(token.size, 4)) == 0) {
    cmd.cmd = TYPE;
  } else if (strncmp(token.token, "cd", MIN(token.size, 2)) == 0) {
    cmd.cmd = CD;
  } else if (token.type == STRING) {
    cmd.cmd = PROGRAM;
  }

  return cmd;
}

