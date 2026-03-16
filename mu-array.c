#include "mu-array.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "mimalloc.h"
#include "mu-general.h"

static void array_checked_resize(struct array* array, uintptr_t additional) {
  assert(array != NULL);

  if (array->count + additional < array->capacity) return;
  uintptr_t new_capacity =
      array->capacity == 0 ? ARRAY_INITIAL : array->capacity * ARRAY_GROWTH;
  while (new_capacity < additional) new_capacity = new_capacity * ARRAY_GROWTH;

  array_resize(array, new_capacity);
}

void array_deinit(struct array* array){
  assert(array != NULL);

  if(array->elems == NULL) return;

  mi_free(array->elems);
  memset(array, 0, sizeof(struct array));
}

void array_resize(struct array* array, uintptr_t new_capacity) {
  assert(array != NULL);
  assert(array->count < new_capacity);

  void* new_elems = mi_zalloc(MU_SIZE(array->size, new_capacity));
  memcpy(new_elems, array->elems, MU_SIZE(array->size, array->count));

  mi_free(array->elems);
  array->elems = new_elems;
  array->capacity = new_capacity;
}

void array_push(struct array* array, void* items, uintptr_t nitems) {
  assert(array != NULL);
  assert(items != NULL);

  array_checked_resize(array, nitems);
  void* location = array_at(array, array->count);
  memcpy(location, items, MU_SIZE(array->size, nitems));

  array->count += nitems;
}

void* array_at(const struct array* array, uintptr_t n) {
  assert(array != NULL);
  assert(array->capacity > n);
  return (char*)array->elems + MU_SIZE(array->size, n);
}
