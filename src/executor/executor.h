#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../parser/parser.h"
#include "../utils/utils.h"
#include "../error/error.h"

bool execute(Prompt *);
Result exec_program(Prompt*);

#endif
