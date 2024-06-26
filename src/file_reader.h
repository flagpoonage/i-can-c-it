#include "sb.h"

typedef enum FileReaderResultCode
{
    FileReadNormal,
    FileReadOpenFileFailed,
    FileReadCloseFileFailed
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
void fr_contents(FileReader *fr, char *dest);