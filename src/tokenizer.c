#include "shell.h"

TokenType get_token_type(char *value) {
  if (strncmp(value, "\"", 1) == 0) {
    return DQUOTE;
  } else if (strncmp(value, "\'", 1) == 0) {
    return QUOTE;
  } else if (strncmp(value, "|'", 1) == 0) {
    return PIPE;
  } else if (strncmp(value, "&", 1) == 0) {
    return AMPERSAND;
  } else if (strncmp(value, ">", 1) == 0) {
    return RIGHTREDIRECTION;
  } else if (strncmp(value, "<", 1) == 0) {
    return LEFTREDIRECTION;
  } else if (strncmp(value, "$", 1) == 0) {
    return DOLLAR;
  }
  return STRING;
}

Token *tokenize(char *input) {
  Token *tokens = (Token *)malloc(sizeof(Token) * 100);
  int count = 0;

  char *value = strtok(input, " ");

  while (value != NULL) {
    TokenType type = get_token_type(value);
    Token token = {type, value};
    tokens[count] = token;
    count++;
    value = strtok(NULL, " ");
  }
  Token token = {EOP, ""};
  tokens[count] = token;

  return tokens;
}
