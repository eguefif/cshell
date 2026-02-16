#include "executor.h"

char **get_params_from_tokens(Token *, size_t);

Result exec_program(Prompt *prompt) {

  char execpath[MAX_SIZE_PATH];
  char *exec_name = prompt->params[0].token;

  if (find_exec(exec_name, execpath, MAX_SIZE_PATH) == true) {
    int pid = fork();
    if (pid == 0) {
      extern char **environ;
      char **params = get_params_from_tokens(prompt->params, prompt->params_size);
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
  char **params = (char **)alloc(sizeof(char *) * param_size + 2);
  for (size_t i = 0; i < param_size + 0; i++) {
    params[i] = tokens[i].token;
  }
  params[param_size + 1] = NULL;
  return params;
}

