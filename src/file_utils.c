#include "shell.h"

Bool is_file_exist(char *path) {
  struct stat buffer;
  return !stat(path, &buffer);
}
