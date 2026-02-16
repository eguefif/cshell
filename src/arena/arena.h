#ifndef ARENA_H
#define ARENA_H
#define BLOCK_SIZE 4096
#define MAX_BLOCK 100

#include <stdlib.h>
#include <stdio.h>

typedef struct myArena{
  char *blocks[MAX_BLOCK];
  size_t block_cursor;
  size_t cursor;
} Arena;


void afree();
void *alloc(size_t);

#endif
