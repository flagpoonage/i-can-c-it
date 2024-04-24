#include "sb.h"

typedef enum FileReaderResultCode
{
  Normal,
  OpenFileFailed,
  CloseFileFailed
} FileReaderResultCode;

typedef struct FileReader
{
  char *filename;
  StringBuilder *_sb;
  FileReaderResultCode code;
} FileReader;

FileReader *fr_init();
FileReaderResultCode fr_readfile(char *filename, FileReader *reader);
void fr_free(FileReader *reader);
void fr_printerr(FileReaderResultCode code);
int fr_contents_len(FileReader *fr);