#include "shell.h"

Bool find_exec(Token token, char *full_path, size_t path_size) {
  char *paths = strdeepcopy(getenv("PATH"));
  char *path = strtok(paths, ":");
  while (path != NULL) {
    if (strlen(path) + strlen(token.token) >= path_size) {
      continue;
    }
    memcpy(full_path, path, strlen(path) + 1);
    strcat(full_path, "/\0");
    strncat(full_path, token.token, strlen(token.token));
    if (!is_exec_exist(full_path)) {
      break;
    }
    path = strtok(NULL, ":");
    full_path[0] = '\0';
  }
  if (full_path[0] == '\0') {
    return FALSE;
  } else {
    return TRUE;
  }
  free(paths);
}

Bool is_exec_exist(char *path) {
  struct stat buffer;
  if (stat(path, &buffer)) {
    return FALSE;
  };
  return (S_ISREG(buffer.st_mode) &&
          ((buffer.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) != 0))
             ? TRUE
             : FALSE;
}
