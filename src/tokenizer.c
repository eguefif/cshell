#include "shell.h"

int skip_white_char(char *);
char *get_string(char *);

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
  Token *tokens = (Token *)malloc(sizeof(Token) * 200);
  int cursor = 0;
  int token_count = 0;
  char *str;

  cursor = skip_white_char(input);
  while (input[cursor] != '\0') {
    switch (input[cursor]) {
    case '\'':
      tokens[token_count] = (Token){QUOTE, &input[cursor]};
      token_count++;
      cursor++;
      break;
    default:
      str = get_string(&input[cursor]);
      // We add one because str is a pointer to a substring of input
      // We just replace the first space after the string by \0
      // The cursor needs to be moved after this \0
      cursor += strlen(str) + 1;
      cursor += skip_white_char(input);
      tokens[token_count] = (Token){STRING, str};
      token_count++;
      break;
    }
  }
  Token token = {EOP, ""};
  tokens[token_count] = token;

  return tokens;
}

int skip_white_char(char *input) {
  int cursor = 0;
  while (is_whitespace(input[cursor]) && !(input[cursor] == '\0')) {
    cursor++;
  }
  return cursor;
}

char *get_string(char *input) {
  int cursor = 0;
  while (!is_whitespace(input[cursor])) {
    cursor++;
  }
  input[cursor] = '\0';
  return input;
}
