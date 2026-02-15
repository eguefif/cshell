#ifndef SHELL_H
#define SHELL_H

#define PROMPT_MAX_SIZE 150
#define MAX_SIZE_PATH 1000
#define MAX_PARAMS 150

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// Tokenizer and Parser functions

typedef enum myResult {
  OK, NOEOL, INPUTTOOLONG, CMDNOTFOUND, EXECVE, CWDERROR
} Result;

typedef enum myTokenType {
  STRING, DQUOTE, QUOTE, PIPE, NUM, AMPERSAND, 
  RIGHTREDIRECTION, LEFTREDIRECTION, EOP, DOLLAR
} TokenType;

typedef struct myToken {
  TokenType type;
  char *token;
} Token;

typedef enum myCommandType {
  PWD, TYPE, ECHO, EXIT, NOTFOUND, PROGRAM
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

typedef struct myShell{
  char **env;
} Shell;

void run_main();
Shell *get_shell();
void init_shell(char **env);

Shell *get_shell();
void parse(Prompt*);
Token *tokenize(char*);
bool execute(Prompt *);
void free_prompt(Prompt);

Result exec_program(Prompt*);

Command get_command(Token token);


// String utils
bool is_whitespace(char);
char *strdeepcopy(char *source);
char *trim_start(char *str);


// File utils
bool is_exec_exist(char*);
bool find_exec(Token, char *, size_t);


// Error handling
bool handle_error(Result, Prompt*);
#endif
