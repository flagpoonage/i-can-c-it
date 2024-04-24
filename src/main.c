#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include "file_reader.h"
// cmai
int main(int argc, char *argv[])
{
  // if (argv[0])
  //   printf("Arg %s", argv[0]);
  if (argc != 2)
  {
    printf("Invalid argument length, expected 2 but got %d", argc);
    exit(1);
  }

  char *fname = argv[1];

  FileReader *fr = fr_init();

  if (fr_readfile(fname, fr) != Normal)
  {
    printf("Failed to read file %s", fname);
    fr_free(fr);
    exit(1);
  }

  printf("%d bytes at: %s\n", fr_contents_len(fr), fr->filename);

  fr_free(fr);

  // = fr_initfile("sb.c");

  // if (fr.code != 0)
  // {
  //   fr_printerr(fr.errcode);
  //   fr_free(&fr);
  //   exit(1);
  // }

  // FileReader fr2;

  // fr_readfile("mem.c", &fr2);

  // StringBuilder stringbuilder;
  // StringBuilder *sb = &stringbuilder;

  // sb_init(sb, 1024, BUFFER_EXPAND_DOUBLE);

  // readfile("sb.c", sb);

  // char outstr[sb->len + 1];

  // sb_tostring(outstr, sb);

  // printf("Read this from the file:\n\n%s", fr.contents);
  // printf("Read this from the file:\n\n%s", fr2.contents);

  // fr_free(&fr);
  // fr_free(&fr2);
}

// int main()
// {
//   struct termios old, new;
//   char c;

//   char *inl;
//   struct StringBuilder stringbuilder;

//   StringBuilder *sb = &stringbuilder;

//   sb_init(sb, 128, BUFFER_EXPAND_DOUBLE);

//   char *q = "This is a list of characters which is longer than the segment size. If I make it even longer it doesn't matter!";

//   const int qlen = strlen(q);

//   int i;

//   for (i = 0; i < qlen; i++)
//   {
//     sb_push(sb, q[i]);
//   }

//   char output_one[stringbuilder.len + 1];

//   sb_tostring(output_one, sb);

//   sb_clear(sb);

//   char output_two[stringbuilder.len + 1];

//   sb_concat(sb, "This is a string, a really cool one?");

//   sb_tostring(output_two, sb);

//   sb_free(sb);

//   printf(
//       "String [%d bytes] [%d buffer]\n%s\n",
//       strlen(output_one),
//       sb->len,
//       output_one);

//   printf(
//       "String [%d bytes] [%d buffer]\n%s\n",
//       strlen(output_two),
//       sb->len,
//       output_two);

//   return 0;
// }
