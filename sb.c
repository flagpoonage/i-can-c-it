#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sb.h"
#include "mem.h"

// static const int SEGMENT_SIZE = 8;
static int expand_storage(StringBuilder *string, int chars);
static int push_bytes(StringBuilder *string, char *bytes, int len);

StringBuilder *sb_init(int init_buffer, short expansion_mode)
{
  StringBuilder *string = must_malloc(sizeof(StringBuilder));
  string->data = must_malloc(init_buffer);
  string->pos = 0;
  string->len = init_buffer;
  string->expansion_mode = expansion_mode == BUFFER_EXPAND_DOUBLE ? BUFFER_EXPAND_DOUBLE : BUFFER_EXPAND_LINEAR;
  return string;
}

void sb_clear(StringBuilder *string)
{
  string->data[0] = '\0';
  string->pos = 0;
}

void sb_free(StringBuilder *string)
{
  free(string->data);
  free(string);
}

char *sb_tostring(char *dest, StringBuilder *string)
{
  strncpy(dest, string->data, string->pos + 1);
  return dest;
}

void sb_push(StringBuilder *string, char c)
{
  expand_storage(string, 1);
  push_bytes(string, &c, 1);
}

int sb_concat(StringBuilder *string, char *target)
{
  // Add one, strlen does not include the null terminator.
  int concat_length = strlen(target) + 1;
  expand_storage(string, concat_length);
  return push_bytes(string, target, concat_length);
}

static int push_bytes(StringBuilder *string, char *bytes, int len)
{
  int i;
  for (i = 0; i < len; i++)
  {
    string->data[string->pos++] = bytes[i];
  }

  string->data[string->pos + 1] = '\0';

  return string->pos;
}

static int expand_storage(StringBuilder *string, int chars)
{
  // Realloc more memory if the current length + chars + terminator length dont fit
  if (string->pos + chars + 1 >= string->len)
  {
    int curr_len = string->len;
    int next_size;

    if (string->expansion_mode == BUFFER_EXPAND_DOUBLE)
    {
      next_size = curr_len * 2;
    }
    else
    {
      next_size = curr_len + string->init_buffer_sz;
    }

    int newbytes = next_size - curr_len;

    string->data = must_realloc(string->data, next_size);

    string->len = next_size;
  }
}