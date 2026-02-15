#include "shell.h"

char **get_params_from_tokens(Token *, size_t);

Result exec_program(Prompt *prompt) {
  char **params = get_params_from_tokens(prompt->params, prompt->params_size);
  extern char **environ;

  params[0] = prompt->cmd.token.token;
  char execpath[MAX_SIZE_PATH];

  if (find_exec(prompt->cmd.token, execpath, MAX_SIZE_PATH) == true) {
    int pid = fork();
    if (pid == 0) {
      execve(execpath, params, environ);
      handle_error(EXECVE, prompt);
      exit(0);
    } else {
      int stat_loc;
      waitpid(pid, &stat_loc, 0);
    }
  } else {
    return CMDNOTFOUND;
  }
  return OK;
}

char **get_params_from_tokens(Token *tokens, size_t param_size) {
  char **params = (char **)malloc(sizeof(char *) * param_size + 2);
  for (size_t i = 1; i < param_size + 1; i++) {
    params[i] = tokens[i - 1].token;
  }
  params[param_size + 1] = NULL;
  return params;
}

