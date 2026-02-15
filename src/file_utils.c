#include "shell.h"

// Find an executble and fill full_path with the path+exec name
// Return true if found and false if no executable was found.
bool find_exec(Token token, char *full_path, size_t path_size) {
  char *paths = strdeepcopy(getenv("PATH"));
  char *path = strtok(paths, ":");
  while (path != NULL) {
    if (strlen(path) + strlen(token.token) >= path_size) {
      continue;
    }
    memcpy(full_path, path, strlen(path) + 1);
    strcat(full_path, "/\0");
    strncat(full_path, token.token, path_size - (strlen(path) + 1));
    if (is_exec_exist(full_path) == true) {
      break;
    }
    path = strtok(NULL, ":");
    full_path[0] = '\0';
  }
  free(paths);
  if (full_path[0] == '\0') {
    return false;
  } else {
    return true;
  }
}

bool is_exec_exist(char *path) {
  struct stat buffer;
  if (stat(path, &buffer) != 0) {
    return false;
  };
  return (S_ISREG(buffer.st_mode) &&
          ((buffer.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) != 0))
             ? true
             : false;
}
