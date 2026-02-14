#include "shell.h"

TokenType get_type(char *value) {
  if (strncmp(value, "\"", 1) == 0) {
    return DQUOTE;
  } else if (strncmp(value, "\'", 1) == 0) {
    return QUOTE;
  } else if (strncmp(value, "|'", 1) == 0) {
    return PIPE;
  } else if (strncmp(value, "&", 1) == 0) {
    return AMPERSAND;
  } else if (strncmp(value, ">", 1) == 0) {
    return REDIRECTION;
  }
  return STRING;
}

Token *tokenize(char *input) {
  Token *tokens = (Token *)malloc(sizeof(Token) * 100);
  int count = 0;

  char *value = strtok(input, " ");

  while (value != NULL) {
    TokenType type = get_type(value);
    Token token = {type, value};
    tokens[count] = token;
    count++;
    value = strtok(NULL, " ");
  }
  Token token = {EOP, ""};
  tokens[count] = token;

  return tokens;
}

Command get_command(Token token) {
  Command cmd = {NOTFOUND, token};
  if (strncmp(token.token, "exit", 4) == 0) {
    cmd.cmd = EXIT;
  } else if (strncmp(token.token, "echo", 4) == 0) {
    cmd.cmd = ECHO;
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
