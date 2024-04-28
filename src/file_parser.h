#include "file_lexer.h"

typedef struct Parser {
    Lexer *lexer;
} Parser;


typedef enum ExpressionType {
    FunctionCallExpression = 0,
    StringLiteralExpression = 1,
    NumberLiteralExpression = 2,
} ExpressionType;

typedef struct TopLevel {
    struct Expression *expressions;
} TopLevel;

typedef struct Literal {
    char *value;
} Literal;

typedef struct Identifier {
    char *value;
} Identifier;

typedef struct FunctionCall {
    char *function_name;
    struct Expression *arguments;
} FunctionCall;

typedef struct Expression {
    ExpressionType type;
    struct FunctionCall *function_call;
    struct Literal *literal;
    struct Identifier *identifier;
} Expression;

Parser *parse_file (char *filename, Parser *parser);
Parser *parse_file_alloc (char *filename);
void parser_free (Parser *parser);