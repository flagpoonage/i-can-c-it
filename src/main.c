#include <stdio.h>

#include "file_parser.h"
#include "util.h"

void maincmp (char *a, char *b);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid argument length, expected 2 but got %d", argc);
        exit(1);
    }

    char *fname = argv[1];
    Parser *parser = parse_file_alloc(fname);
    LexerToken *tokens = parser->lexer->tokens;

    int i;
    for(i = 0; i < parser->lexer->token_count; i++) {
        printf("Lexed[%d]: [T%d] %s\n", i, tokens[i].type, tokens[i].string);
    }

    printf("\n%s is (: %s", tokens[0].string, STREQ(tokens[0].string, "(") ? "true": "false");

    parser_free(parser);
}