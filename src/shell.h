#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

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
  TYPE, ECHO, EXIT, NOTFOUND, PROGRAM
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

typedef struct myShell{
  char **env;
} Shell;

Prompt parse(char*);
Token *tokenize(char*);
Bool execute(Prompt prompt);
Shell *get_shell();

Command get_command(Token token);


// String utils
Bool is_whitespace(char);
char *strdeepcopy(char *source);
char *trim_start(char *str);


// File utils
Bool is_exec_exist(char*);
Bool find_exec(Token, char *, size_t);
#endif
