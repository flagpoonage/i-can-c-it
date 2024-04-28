#include "file_lexer.h"

typedef struct Parser {
    Lexer *lexer;
} Parser;

Parser *parse_file (char *filename, Parser *parser);
Parser *parse_file_alloc (char *filename);
void parser_free (Parser *parser);