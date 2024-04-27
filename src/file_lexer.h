
#include "file_reader.h"

typedef enum TokenType {
    TokenTypeNone = 0,
    TokenTypeOpenParen = 1,
    TokenTypeCloseParen = 2,
    TokenTypeIdentifier = 3,
    TokenTypeNumeric = 4,
    TokenTypeString = 5
} TokenType;

typedef struct LexerToken {
    TokenType type;
    char *string;
} LexerToken;

typedef struct Lexer {
    char * _string_buffer;
    FileReader *_fr;
    LexerToken *tokens;
    int token_count;
} Lexer;

Lexer *lex_file_alloc (char *filename);
Lexer *lex_file (char *string, Lexer *lexer);
void lex_free (Lexer *lex);
int lex_sourcelen(Lexer *lex);
void lex_getsource(Lexer *lex, char *dest);
void lexer_token_sprint(LexerToken *token);