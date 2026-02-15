#include "shell.h"

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
