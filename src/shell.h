#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tokenizer and Parser functions

typedef enum myBool {
  TRUE, FALSE,
} Bool;

typedef enum myTokenType {
  STRING, DQUOTE, QUOTE, PIPE, NUM, AMPERSAND, 
  RIGHTREDIRECTION, LEFTREDIRECTION, EOP, DOLLAR
} TokenType;

typedef struct myToken {
  TokenType type;
  char *token;
} Token;

typedef enum myCommandType {
  ECHO, EXIT, NOTFOUND,
} CommandType;

typedef struct myCommand {
  CommandType cmd;
  Token token;
} Command;

typedef struct myPrompt {
  Command cmd;
  Token *params;
  int params_size;
} Prompt;

Prompt parse(char*);
Token *tokenize(char*);

#endif
