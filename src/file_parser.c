#include "file_parser.h"
#include "mem.h"

Parser *parse_file (char *filename, Parser *parser) {
    parser->lexer = lex_file_alloc(filename);
    LexerToken *tokens = parser->lexer->tokens;
    int token_pos = 0;

    TopLevel *tl = must_calloc(1, sizeof(TopLevel));

    // This is quite a lot more than the theoretical maxium of expressions,
    // because there's so many expressions that contain more than a single token
    // but this is a large enough size that it shouldn't fail.
    Expression *exp_buffer = must_calloc(parser->lexer->token_count, sizeof(Expression));

    int expression_pos = 0;

    Expression *current_tl;
    Expression *exp_current;

    while(token_pos < parser->lexer->token_count) {
        LexerToken current_token = tokens[token_pos];

        if (current_tl == NULL) {
            if (current_token.type == TokenTypeOpenParen) {
                current_tl = &tl->expressions[expression_pos++];
                current_tl->function_call = must_calloc(1, sizeof(FunctionCall));
                current_tl->type = FunctionCallExpression;

                int i;
                for (i = 0; i < 5; i++) {
                    // Basically only allowing 5 arguments here, which is pretty dumb
                    // because we'll definitely need more than that.
                    current_tl->function_call->arguments[i] = tl->expressions[expression_pos++];
                }

                // We haven't checked, but if there isn't a current top level, then
                // we shouldn't really have a current expression. Maybe you should
                // check that.
                exp_current = current_tl;
            }
            else {
                printf("Unexpected token [%s] outside of expression", current_token.string);
                exit(1);
            }

            continue;
        }

        if (current_token.type == TokenTypeOpenParen) {
            if (exp_current->function_call == NULL) {
                printf("Unexpected open-parens at start of another expression");
                exit(1);
            }

            exp_current->function_call->arguments
        }




        printf(
            "Parsing token[%d]: [T%d] %s\n",
            token_pos,
            tokens[token_pos].type,
            tokens[token_pos].string);
        token_pos++;
    }

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