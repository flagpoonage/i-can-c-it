#include <string.h>
#include <ctype.h>

#include "mem.h"
#include "file_lexer.h"

#define IS_WHITESPACE(c) c == ' ' || c == '\n' || c == '\r'

#define SINGLE_CHAR_TOKEN(buffer, bpos, strptr, tokens, tpos, chr, currentToken, tokenType) {\
                            buffer[bpos++] = chr;\
                            buffer[bpos++] = '\0';\
                            tokens[tpos].string = strptr;\
                            tokens[tpos].type = currentToken;\
                            tpos++;\
                            tokenType = TokenTypeNone;\
                            strptr = sb + bpos; }

#define FINALIZE_TOKEN(buffer, bpos, strptr, tokens, tpos, finalChar, tokenType) {\
                            buffer[bpos++] = finalChar;\
                            buffer[bpos++] = '\0';\
                            tokens[tpos].string = strptr;\
                            tokens[tpos].type = tokenType;\
                            tpos++;\
                            tokenType = TokenTypeNone;\
                            strptr = sb + bpos; }

#define END_TOKEN(buffer, bpos, strptr, tokens, tpos, tokenType) {\
                            buffer[bpos++] = '\0';\
                            tokens[tpos].string = strptr;\
                            tokens[tpos].type = tokenType;\
                            tpos++;\
                            tokenType = TokenTypeNone;\
                            strptr = sb + bpos; }

static Lexer *init(char *filename) {
    FileReader *fr = fr_init();
    FileReaderResultCode read_result = fr_readfile(filename, fr);

    if (read_result == FileReadOpenFileFailed) {
        printf("Failed to read file %s", filename);
        fr_free(fr);
        exit(1);
    }
    else if (read_result == FileReadCloseFileFailed) {
        printf("Error closing file [%s], although it's probably still closed", filename);
    }

    Lexer *lexer = must_calloc(1, sizeof(Lexer));
    lexer->_fr = fr;
    lexer->token_count = 0;
    lexer->_string_buffer = must_calloc(1, fr_contents_len(fr) * 2);
    return lexer;
}


Lexer *lex_file (char *filename, Lexer *lexer)
{
    int len = fr_contents_len(lexer->_fr);
    printf("Source length is %d\n", fr_contents_len(lexer->_fr));
    char source[len];

    int q;
    for(q = 0; q < len; q++) {
        // Zero the string, stop memory complaints
        source[q] = '\0';
    }

    fr_contents(lexer->_fr, source);
    int source_pos = 0, buffer_pos = 0;
    char *sb = lexer->_string_buffer;
    char *strptr = lexer->_string_buffer;
    TokenType token_type = TokenTypeNone;

    // TODO: This should be dynamically allocated, 1000 tokens won't
    // last too longs
    LexerToken *tokens = must_calloc(1000, sizeof(LexerToken));

    lexer->tokens = tokens;

    int token_pos = 0;

    while (source_pos < len) {
        char next_char = source[source_pos++];

        int is_open_paren = next_char == '(';
        int is_close_paren = next_char == ')';
        int is_paren = is_open_paren || is_close_paren;
        int is_string_delim = next_char == '"';
        int is_number = !is_paren && !is_string_delim && !isdigit(next_char);
        int is_whitespace = IS_WHITESPACE(next_char);
        int is_reading_token = token_type != TokenTypeNone;

        if (token_type == TokenTypeString) {
            // We're currently reading a string, so we take whatever characters
            // we're given, unless it's a string delimiter.
            // TODO: Handle string delimiter escaping like \"

            if (is_string_delim) {
                // We've reached the end of the string,
                FINALIZE_TOKEN(
                    sb, buffer_pos, strptr, tokens, token_pos, next_char, token_type);
            }
            else {
                // The strings not finished, so just add another character
                sb[buffer_pos++] = next_char;
            }

            continue;
        }

        // We can only check this after string checks, because white space is
        // meaninful inside a string
        if (is_whitespace) {
            if (is_reading_token) {
                // We're entering whitespace, and we were previously reading
                // a token. That means the token has ended. The whitespace that
                // we're now reading shouldn't be included
                END_TOKEN(
                    sb, buffer_pos, strptr, tokens, token_pos, token_type);
            }

            // Just continue through the whitespace
            continue;
        }

        if (is_paren) {
            if (is_reading_token) {
                // We've reached a parenthesis, so we end this the current token
                // that's being read.
                END_TOKEN(
                    sb, buffer_pos, strptr, tokens, token_pos, token_type);
            }
            // A parenthesis is a single character token, so we can set all the buffers
            // here in one go.
            TokenType parens_type = is_open_paren ? TokenTypeOpenParen : TokenTypeCloseParen;
            SINGLE_CHAR_TOKEN(
                sb, buffer_pos, strptr, tokens, token_pos, next_char, parens_type, token_type);

            continue;
        }

        // If we reach here, this is a non-whitespace character, that's not
        // inside of a string, and isn't a parenthesis, so whatever it is, it's
        // part of a string that we want to capture either for a new token, or
        // an existing token that we're reading through.
        sb[buffer_pos++] = next_char;

        if (is_string_delim) {
            if (token_type == TokenTypeNone) {
                token_type = TokenTypeString;
            }

            continue;
        }

        if (!is_number) {
            if (token_type == TokenTypeNumeric || token_type == TokenTypeNone) {
                // This is either a new token, or we're reading a numeric token
                // in which case it has non numeric digits, so we convert it to
                // an identifier.
                token_type = TokenTypeIdentifier;
            }
        }
        else if (token_type == TokenTypeNone) {
            // We're starting a new token, and it starts with a number so we'll
            // initially set it as a numeric token.
            token_type = TokenTypeNumeric;
        }
    }

    sb[buffer_pos++] = '\0';
    tokens[token_pos].string = strptr;
    tokens[token_pos].type = token_type;

    lexer->token_count = token_pos + 1;

    return lexer;
}

Lexer *lex_file_alloc (char *filename)
{
    Lexer *lexer = init(filename);
    return lex_file(filename, lexer);
}

void lex_free (Lexer *lex)
{
    fr_free(lex->_fr);
    free(lex->_string_buffer);
    free(lex->tokens);
    free(lex);
}

int lex_sourcelen(Lexer *lex)
{
    return fr_contents_len(lex->_fr);
}

void lex_getsource(Lexer *lex, char *dest)
{
    fr_contents(lex->_fr, dest);
}