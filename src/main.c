#include <stdio.h>

#include "file_reader.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid argument length, expected 2 but got %d", argc);
        exit(1);
    }

    char *fname = argv[1];
    FileReader *fr = fr_init();
    FileReaderResultCode read_result = fr_readfile(fname, fr);

    if (read_result == FileReadOpenFileFailed)
    {
        printf("Failed to read file %s", fname);
        fr_free(fr);
        exit(1);
    }
    else if (read_result == FileReadCloseFileFailed)
    {
        printf("Error closing file [%s], although it's probably still closed", fname);
    }

    char contents[fr_contents_len(fr)];
    fr_contents(fr, contents);

    printf("%d bytes at: %s\n\n%s\n", fr_contents_len(fr), fr->filename, contents);

    fr_free(fr);
}