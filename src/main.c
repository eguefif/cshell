#include "shell.h"


int main(int argc, char **argv, char **env) {
  // Flush after every printf
  setbuf(stdout, NULL);

  if (argc > 1) {
    printf("Usage: %s\n", argv[0]);
    exit(0);
  }

  init_shell(env);
  run_main();

  return 0;
}
