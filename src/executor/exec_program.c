#include "executor.h"

char **get_params_from_tokens(Token *, size_t);

Result exec_program(Prompt *prompt) {

  char execpath[MAX_SIZE_PATH];

  Command cmd = prompt->cmd;
  char *exec_name = malloc(cmd.token.size + 1);
  memcpy(exec_name, cmd.token.token, cmd.token.size);
  exec_name[cmd.token.size] = '\0';

  if (find_exec(exec_name, execpath, MAX_SIZE_PATH) == true) {
    int pid = fork();
    if (pid == 0) {
      char **params = get_params_from_tokens(prompt->params, prompt->params_size);
      params[0] = exec_name;
      extern char **environ;
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
    Token token = tokens[i - 1];
    char *param = malloc(token.size + 1);
    memcpy(param, token.token, token.size);
    param[token.size] = '\0';
    params[i] = param;
  }
  params[param_size + 1] = NULL;
  return params;
}

