#pragma once

#include <stdint.h>

#define ARRAY_INITIAL 4
#define ARRAY_GROWTH 2

struct array {
  void* elems;
  uintptr_t size;
  uintptr_t count, capacity;
};

void array_resize(struct array* array, uintptr_t new_capacity);
void array_push(struct array* array, void* items, uintptr_t nitems);
void* array_at(const struct array* array, uintptr_t n);

struct slice {
  void* ptr;
  uintptr_t len;
};

#define slice_init(ptr, len) ((struct slice){ptr, len})

