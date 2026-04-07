#include "parser.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* Forward declarations */
static double parse_expression(const char* expr, int* pos);
static double parse_term(const char* expr, int* pos);
static double parse_factor(const char* expr, int* pos);
static double parse_number(const char* expr, int* pos);
static double apply_function(const char* func_name, double arg);
static double apply_function_two_args(const char* func_name, double arg1, double arg2);

/* Skip whitespace */
static void skip_whitespace(const char* expr, int* pos) {
    while (expr[*pos] && isspace(expr[*pos])) {
        (*pos)++;
    }
}

/* Parse constants like PI, E */
static bool parse_constant(const char* expr, int* pos, double* value) {
    skip_whitespace(expr, pos);
    
    if (strncmp(&expr[*pos], "pi", 2) == 0 || strncmp(&expr[*pos], "PI", 2) == 0) {
        *value = PI;
        *pos += 2;
        return true;
    }
    if (strncmp(&expr[*pos], "e", 1) == 0 && !isalnum(expr[*pos + 1])) {
        *value = E;
        *pos += 1;
        return true;
    }
    if (strncmp(&expr[*pos], "phi", 3) == 0) {
        *value = GOLDEN_RATIO;
        *pos += 3;
        return true;
    }
    return false;
}

/* Parse function names */
static bool parse_function(const char* expr, int* pos, char* func_name) {
    skip_whitespace(expr, pos);
    
    if (!isalpha(expr[*pos])) {
        return false;
    }
    
    int i = 0;
    while (isalpha(expr[*pos]) && i < 31) {
        func_name[i++] = expr[*pos];
        (*pos)++;
    }
    func_name[i] = '\0';
    return true;
}

/* Apply unary function */
static double apply_function(const char* func_name, double arg) {
    if (strcmp(func_name, "sin") == 0) return func_sin(arg);
    if (strcmp(func_name, "cos") == 0) return func_cos(arg);
    if (strcmp(func_name, "tan") == 0) return func_tan(arg);
    if (strcmp(func_name, "asin") == 0) return func_asin(arg);
    if (strcmp(func_name, "acos") == 0) return func_acos(arg);
    if (strcmp(func_name, "atan") == 0) return func_atan(arg);
    if (strcmp(func_name, "ln") == 0) return func_ln(arg);
    if (strcmp(func_name, "log") == 0) return func_log10(arg);
    if (strcmp(func_name, "log2") == 0) return func_log2(arg);
    if (strcmp(func_name, "log10") == 0) return func_log10(arg);
    if (strcmp(func_name, "sqrt") == 0) return func_sqrt(arg);
    if (strcmp(func_name, "cbrt") == 0) return func_cbrt(arg);
    if (strcmp(func_name, "abs") == 0) return func_abs(arg);
    if (strcmp(func_name, "floor") == 0) return func_floor(arg);
    if (strcmp(func_name, "ceil") == 0) return func_ceil(arg);
    if (strcmp(func_name, "round") == 0) return func_round(arg);
    if (strcmp(func_name, "exp") == 0) return func_exp(arg);
    if (strcmp(func_name, "factorial") == 0 || strcmp(func_name, "fact") == 0) return func_factorial(arg);
    if (strcmp(func_name, "sin_deg") == 0) return func_sin(deg_to_rad(arg));
    if (strcmp(func_name, "cos_deg") == 0) return func_cos(deg_to_rad(arg));
    if (strcmp(func_name, "tan_deg") == 0) return func_tan(deg_to_rad(arg));
    
    return arg; // Unknown function, return argument
}

/* Parse primary factor (number, function, or parenthesized expression) */
static double parse_factor(const char* expr, int* pos) {
    skip_whitespace(expr, pos);
    
    double value = 0.0;
    
    // Handle unary plus/minus
    int sign = 1;
    if (expr[*pos] == '+') {
        (*pos)++;
        skip_whitespace(expr, pos);
    } else if (expr[*pos] == '-') {
        sign = -1;
        (*pos)++;
        skip_whitespace(expr, pos);
    }
    
    // Try to parse constant
    if (parse_constant(expr, pos, &value)) {
        return sign * value;
    }
    
    // Try to parse function
    char func_name[32];
    if (parse_function(expr, pos, func_name)) {
        skip_whitespace(expr, pos);
        if (expr[*pos] == '(') {
            (*pos)++;
            double arg = parse_expression(expr, pos);
            skip_whitespace(expr, pos);
            if (expr[*pos] == ')') {
                (*pos)++;
            }
            return sign * apply_function(func_name, arg);
        }
    }
    
    // Parse number
    if (isdigit(expr[*pos]) || expr[*pos] == '.') {
        value = parse_number(expr, pos);
        return sign * value;
    }
    
    // Parse parenthesized expression
    if (expr[*pos] == '(') {
        (*pos)++;
        value = parse_expression(expr, pos);
        skip_whitespace(expr, pos);
        if (expr[*pos] == ')') {
            (*pos)++;
        }
        return sign * value;
    }
    
    return 0.0;
}

/* Parse number */
static double parse_number(const char* expr, int* pos) {
    double value = 0.0;
    int decimal_places = 0;
    bool in_decimal = false;
    
    while (isdigit(expr[*pos]) || (expr[*pos] == '.' && !in_decimal)) {
        if (expr[*pos] == '.') {
            in_decimal = true;
            (*pos)++;
        } else {
            int digit = expr[*pos] - '0';
            if (in_decimal) {
                decimal_places++;
                value += digit / pow(10, decimal_places);
            } else {
                value = value * 10 + digit;
            }
            (*pos)++;
        }
    }
    
    return value;
}

/* Parse exponentiation (highest precedence) */
static double parse_exponent(const char* expr, int* pos) {
    double result = parse_factor(expr, pos);
    skip_whitespace(expr, pos);
    
    while (expr[*pos] == '^') {
        (*pos)++;
        double right = parse_factor(expr, pos);
        result = func_power(result, right);
        skip_whitespace(expr, pos);
    }
    
    return result;
}

/* Parse term (multiplication and division) */
static double parse_term(const char* expr, int* pos) {
    double result = parse_exponent(expr, pos);
    skip_whitespace(expr, pos);
    
    while (expr[*pos] == '*' || expr[*pos] == '/' || expr[*pos] == '%') {
        char op = expr[*pos];
        (*pos)++;
        double right = parse_exponent(expr, pos);
        
        if (op == '*') {
            result = func_multiply(result, right);
        } else if (op == '/') {
            result = func_divide(result, right);
        } else if (op == '%') {
            result = func_modulo(result, right);
        }
        skip_whitespace(expr, pos);
    }
    
    return result;
}

/* Parse expression (addition and subtraction) */
static double parse_expression(const char* expr, int* pos) {
    double result = parse_term(expr, pos);
    skip_whitespace(expr, pos);
    
    while (expr[*pos] == '+' || expr[*pos] == '-') {
        char op = expr[*pos];
        (*pos)++;
        double right = parse_term(expr, pos);
        
        if (op == '+') {
            result = func_add(result, right);
        } else {
            result = func_subtract(result, right);
        }
        skip_whitespace(expr, pos);
    }
    
    return result;
}

bool parser_evaluate(const char* expression, double* result) {
    if (!expression || !result) {
        return false;
    }
    
    int pos = 0;
    *result = parse_expression(expression, &pos);
    
    // Check if entire expression was parsed
    skip_whitespace(expression, &pos);
    return expression[pos] == '\0';
}

int parser_tokenize(const char* expression, Token* tokens) {
    // Placeholder for tokenization
    // This would be used for more advanced parsing if needed
    return 0;
}
