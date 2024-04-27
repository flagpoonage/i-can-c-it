#include <stdio.h>

#include "file_lexer.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid argument length, expected 2 but got %d", argc);
        exit(1);
    }

    char *fname = argv[1];
    Lexer *lex = lex_file_alloc(fname);

    int i;
    for(i = 0; i < lex->token_count; i++) {
        printf("Lexed[%d]: [T%d] %s\n", i, lex->tokens[i].type, lex->tokens[i].string);
    }

    lex_free(lex);
}
