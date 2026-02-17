#include "./parser.h"

Command get_command(Token);
char *concat_params(Token *, size_t, int);

void parse(Prompt *prompt) {
  Token *tokens = tokenize(prompt->input);
  Command cmd = get_command(tokens[0]);

  int i = 0;
  int n = 0;
  size_t param_size = 0;
  size_t params_counter = 0;
  while (true) {
    // TODO: This stop should be with all stop value
    // We concat with | and > too
    if (tokens[i].type == SPACE) {
      prompt->params[params_counter].token = concat_params(&tokens[i - n], param_size, n);
      prompt->params[params_counter].type = STRING;
      prompt->params[params_counter].size = param_size;
      params_counter += 1;
      param_size = 0;
      n = 0;
    }  else if (tokens[i].type == EOP){
      if (n >= 0) {
        prompt->params[params_counter].token = concat_params(&tokens[i - n], param_size, n);
        prompt->params[params_counter].type = STRING;
        prompt->params[params_counter].size = param_size;
      }
      break;
    } else {
      param_size += strlen(tokens[i].token);
      n++;
    }
    i++;
  }
  prompt->params_size = params_counter + 1;
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

char *concat_params(Token *tokens, size_t size, int n) {
  char *retval = alloc(size + 1);
  for (int i = 0; i < n; i++) {
    strncat(retval, tokens[i].token, size);
  }
  return retval;
}
