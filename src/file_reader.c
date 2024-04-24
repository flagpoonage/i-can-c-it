#include <stdio.h>
#include <string.h>
#include "file_reader.h"
#include "mem.h"

static FileReaderResultCode readfile_tosb(char *filename, StringBuilder *sb)
{
  char c;
  char bytes[128];
  FILE *file;

  // Clean any data
  sb_clear(sb);

  file = fopen(filename, "r");

  if (file == NULL)
  {
    return OpenFileFailed;
  }

  while ((c = fgetc(file)) != EOF)
  {
    sb_push(sb, c);
  }

  if (fclose(file) == EOF)
  {
    printf("Failed to close file");
    return CloseFileFailed;
  }

  return Normal;
}

FileReaderResultCode fr_readfile(char *filename, FileReader *reader)
{
  reader->filename = strdup(filename);
  reader->code = readfile_tosb(filename, reader->_sb);
  return reader->code;
}

void fr_free(FileReader *reader)
{
  sb_free(reader->_sb);
  free(reader->filename);
  free(reader);
}

FileReader *fr_init()
{
  FileReader *fr = must_malloc(sizeof(FileReader));
  StringBuilder *sb;
  fr->_sb = sb_init(1024, BUFFER_EXPAND_DOUBLE);
  return fr;
}

int fr_contents_len(FileReader *fr)
{
  return fr->_sb->pos + 2;
}

void fr_getcontents(char *)
{
}