#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

/**
 * @file parser.h
 * @brief Expression parser with operator precedence
 */

#define MAX_TOKENS 100

typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_FUNCTION,
    TOKEN_CONSTANT,
    TOKEN_ERROR,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    double value;
    char op;
    char function[32];
} Token;

/**
 * Parse and evaluate expression
 * @param expression Input expression string
 * @param result Output for the result
 * @return true if parsing was successful
 */
bool parser_evaluate(const char* expression, double* result);

/**
 * Tokenize expression string
 * @param expression Input expression
 * @param tokens Output token array
 * @return Number of tokens
 */
int parser_tokenize(const char* expression, Token* tokens);

#endif // PARSER_H
