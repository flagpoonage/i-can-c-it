#include "file_parser.h"
#include "mem.h"

Parser *parse_file (char *filename, Parser *parser) {
    parser->lexer = lex_file_alloc(filename);
    return parser;
}

Parser *parse_file_alloc (char *filename) {
    Parser *parser = must_calloc(1, sizeof(Parser));
    parse_file(filename, parser);
    return parser;
}

void parser_free (Parser *parser) {
    lex_free(parser->lexer);
    free(parser);
}