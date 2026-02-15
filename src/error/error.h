#ifndef ERROR_H
#define ERROR_H

#include "../parser/parser.h"

typedef enum myResult {
  OK, NOEOL, INPUTTOOLONG, CMDNOTFOUND, EXECVE, CWDERROR,
  CDPARAMS, CDERROR, CDNOHOME,
} Result;


bool handle_error(Result, Prompt*);

#endif
