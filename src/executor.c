#include "shell.h"

void exec_echo(Prompt);
void exec_type(Token);
void handle_type_program(Token token);
void exec_program(Prompt);

bool execute(Prompt prompt) {
  switch (prompt.cmd.cmd) {
  case PROGRAM:
    exec_program(prompt);
    break;
  case ECHO:
    exec_echo(prompt);
    break;
  case EXIT:
    return false;
  case TYPE:
    exec_type(prompt.params[0]);
    break;
  case NOTFOUND:
    printf("%s: command not found\n", prompt.cmd.token.token);
    break;
  }
  return true;
}

void exec_echo(Prompt prompt) {
  for (size_t i = 0; i < prompt.params_size - 1; i++) {
    printf("%s ", prompt.params[i].token);
  }
  printf("%s\n", prompt.params[prompt.params_size - 1].token);
}

void exec_type(Token token) {
  Command cmd = get_command(token);
  switch (cmd.cmd) {
  case ECHO:
    printf("echo is a shell builtin\n");
    break;
  case EXIT:
    printf("exit is a shell builtin\n");
    break;
  case TYPE:
    printf("type is a shell builtin\n");
    break;
  case PROGRAM:
    handle_type_program(token);
    break;
  case NOTFOUND:
    handle_type_program(token);
    break;
  default:
    printf("%s: not found\n", cmd.token.token);
    break;
  }
}

void handle_type_program(Token token) {
  char fullpath[250];

  if (find_exec(token, fullpath, 250)) {
    printf("%s: not found\n", token.token);
  } else {
    printf("%s is %s\n", token.token, fullpath);
  }
}

char **get_params_from_tokens(Token *tokens, size_t param_size) {
  char **params = (char **)malloc(sizeof(char *) * param_size + 2);
  for (size_t i = 1; i < param_size + 1; i++) {
    params[i] = tokens[i - 1].token;
  }
  params[param_size + 1] = NULL;
  return params;
}

// TODO: handle path too long error
void exec_program(Prompt prompt) {
  char **params = get_params_from_tokens(prompt.params, prompt.params_size);
  params[0] = prompt.cmd.token.token;
  char execpath[250];
  if (find_exec(prompt.cmd.token, execpath, 250) == true) {
    extern char **environ;
    int pid = fork();
    if (pid == 0) {
      execve(execpath, params, environ);
      printf("error %s\n", strerror(errno));
      exit(0);
    } else {
      int stat_loc;
      waitpid(pid, &stat_loc, 0);
    }
  } else {
    printf("%s: command not found\n", prompt.cmd.token.token);
  }
}
