#ifndef PARSER_H
#define PARSER_H

#include "../shell.h"
#include "../utils/utils.h"

typedef enum myTokenType {
  STRING, DQUOTE, QUOTE, PIPE, NUM, AMPERSAND, 
  RIGHTREDIRECTION, LEFTREDIRECTION, EOP, DOLLAR,
  TILD, SPACE
} TokenType;

typedef struct myToken {
  TokenType type;
  char *token;
  size_t size;
} Token;

typedef enum myCommandType {
  CD, PWD, TYPE, ECHO, EXIT, NOTFOUND, PROGRAM
} CommandType;

typedef struct myCommand {
  CommandType cmd;
  Token token;
} Command;

typedef struct myPrompt {
  char input[PROMPT_MAX_SIZE];
  Command cmd;
  Token params[MAX_PARAMS];
  size_t params_size;
} Prompt;


void parse(Prompt*);
Token *tokenize(char*);

Command get_command(Token);

#endif
