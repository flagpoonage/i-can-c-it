#include <stdio.h>
#include <stdlib.h>

void *must_malloc(size_t size);
void *must_realloc(void *ptr, size_t size);
void *must_calloc(size_t members, size_t size);