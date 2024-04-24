#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

typedef struct StringBuilder
{
  char *data;
  int len;
  int pos;
  short expansion_mode;
  int init_buffer_sz;
} StringBuilder;

#define BUFFER_EXPAND_DOUBLE 0
#define BUFFER_EXPAND_LINEAR 1

StringBuilder *sb_init(int init_buffer, short expansion_mode);
void sb_free(StringBuilder *string);
char *sb_tostring(char *dest, StringBuilder *string);
void sb_push(StringBuilder *string, char c);
int sb_concat(StringBuilder *string, char *target);
void sb_clear(StringBuilder *string);
