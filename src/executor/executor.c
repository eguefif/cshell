#include "executor.h"

void exec_echo(Prompt*);
void exec_type(Token);
Result exec_cd(Prompt*);
Result exec_pwd();
void handle_type_program(Token token);

bool execute(Prompt *prompt) {
  Result res = OK;
  switch (prompt->cmd.cmd) {
  case PROGRAM:
    res = exec_program(prompt);
    break;
  case ECHO:
    exec_echo(prompt);
    break;
  case PWD:
    res = exec_pwd();
    break;
  case CD:
    res = exec_cd(prompt);
    break;
  case EXIT:
    return false;
  case TYPE:
    // TODO: Handle error no type param
    exec_type(prompt->params[1]);
    break;
  case NOTFOUND:
    printf("%s: command not found\n", prompt->cmd.token.token);
    break;
  }
  if (res != OK) {
    handle_error(res, prompt);
  }
  return true;
}

void exec_echo(Prompt *prompt) {
  size_t i = 0;
  Token *tokens = prompt->params;

  for(i = 1 ; i < prompt->params_size - 1; i++) {
    Token token = tokens[i];
    write(1, token.token, token.size);
    write(1, &" ", 1);
  }
  write(1, tokens[i].token, tokens[i].size);
  write(1, &"\n", 2);
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
  case PWD:
    printf("pwd is a shell builtin\n");
    break;
  case TYPE:
    printf("type is a shell builtin\n");
    break;
  case CD:
    printf("cd is a shell builtin\n");
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

  if (find_exec(token.token, fullpath, 250)) {
    printf("%s is %s\n", token.token, fullpath);
  } else {
    printf("%s: not found\n", token.token);
  }
}

Result exec_pwd() {
  char path[MAX_SIZE_PATH];
  if (getcwd(path, MAX_SIZE_PATH) == NULL) {
    return CWDERROR;
  }
  printf("%s\n", path);
  return OK;
}

Result exec_cd(Prompt *prompt) {
  char path[MAX_SIZE_PATH] = {0};

  if (prompt->params_size == 1 || (prompt->params_size >= 2 && prompt->params[1].token[0] == '~')) {
    char *home_path = getenv("HOME");
    if (home_path == NULL) {
      return CDNOHOME;
    }
    // TODO: Handle error path size too large
    memcpy(path, home_path, strlen(home_path) + 1);
  }
  if (prompt->params_size >= 2 && prompt->params[1].token[0] != '~') {
    char *param_path = prompt->params[1].token;
    strncat(path, param_path, MAX_SIZE_PATH - strlen(path));
  }

  if (chdir(path) == 0) {
    return OK;
  }
  return CDERROR;
}
