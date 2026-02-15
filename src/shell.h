#ifndef SHELL_H
#define SHELL_H

#define PROMPT_MAX_SIZE 150
#define MAX_PARAMS 150

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// Tokenizer and Parser functions

// TODO: Refactor TRUE and FALSE to to true false and bool
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
  char input[PROMPT_MAX_SIZE];
  Command cmd;
  Token params[MAX_PARAMS];
  int params_size;
} Prompt;

typedef struct myShell{
  char **env;
} Shell;

Shell *get_shell();
void parse(Prompt*);
Token *tokenize(char*);
Bool execute(Prompt prompt);
void free_prompt(Prompt);

Command get_command(Token token);


// String utils
Bool is_whitespace(char);
char *strdeepcopy(char *source);
char *trim_start(char *str);


// File utils
Bool is_exec_exist(char*);
Bool find_exec(Token, char *, size_t);
#endif
