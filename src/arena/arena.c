#include "arena.h"

Arena *get_arena();
int alloc_block(Arena*);

void *alloc(size_t size) {
  Arena *arena = get_arena();
  if (arena->cursor + size >= BLOCK_SIZE) {
    if (alloc_block(arena) == 0) {
      return NULL;
    }
  }
  void *pointer = &(arena->blocks[arena->cursor]);
  arena->cursor += size;
  return pointer;
} 

void *afree() {
  Arena *arena = get_arena();
  arena->block_cursor = 0;
  arena->cursor = 0;
}

Arena *get_arena() {
  static Arena *arena = {0};
  if (arena->blocks == NULL) {
    printf("Initialized first block");
    arena->blocks[0] = malloc(BLOCK_SIZE);
  }
  return arena;
}

int alloc_clock(Arena* arena) {
  arena->block_cursor++;
  if (arena->block_cursor >= MAX_BLOCK) {
    return 0;
  }
  void *new_block = malloc(BLOCK_SIZE);
  arena->blocks[arena->block_cursor] = new_block;
  arena->cursor = 0;
  return 1;
}
