#include <stdio.h>
#include <stdlib.h>

#include "mem.h"

void *must_malloc(size_t size)
{
  void *ptr;
  if ((ptr = malloc(size)) == NULL)
  {
    printf("Failed asdto malloc");
    exit(1);
  }
  return ptr;
}

void *must_realloc(void *ptr, size_t size)
{
  if ((ptr = realloc(ptr, size)) == NULL)
  {
    printf("Failed to realloc");
    exit(1);
  }

  return ptr;
}

void *must_calloc(size_t members, size_t size)
{
  void *ptr;
  if ((ptr = calloc(members, size)) == NULL)
  {
    printf("Failed to calloc");
    exit(1);
  }

  return ptr;
}