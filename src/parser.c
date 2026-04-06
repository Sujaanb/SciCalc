/**
 * @file parser.c
 * @brief Expression parser implementation
 * @author Sujaan Bhattacharyya
 * @version 1.0.0
 */

#include "../include/parser.h"
#include <string.h>
#include <ctype.h>

/**
 * @brief Parse operator character to operation type
 */
OperationType parse_operator(char op) {
    switch (op) {
        case '+':
            return OP_ADD;
        case '-':
            return OP_SUBTRACT;
        case '*':
            return OP_MULTIPLY;
        case '/':
            return OP_DIVIDE;
        case '^':
            return OP_POWER;
        case '%':
            return OP_MODULO;
        default:
            return OP_INVALID;
    }
}

/**
 * @brief Parse function name string to operation type
 */
OperationType parse_function(const char *func_name) {
    if (!func_name) return OP_INVALID;
    
    /* Convert to lowercase for comparison */
    char lower_name[32] = {0};
    for (int i = 0; i < sizeof(lower_name) - 1 && func_name[i]; i++) {
        lower_name[i] = tolower((unsigned char)func_name[i]);
    }
    
    /* Binary functions */
    if (strcmp(lower_name, "pow") == 0) return OP_POWER;
    if (strcmp(lower_name, "mod") == 0) return OP_MODULO;
    
    /* Unary algebraic functions */
    if (strcmp(lower_name, "sqrt") == 0) return OP_SQRT;
    if (strcmp(lower_name, "cbrt") == 0) return OP_CBRT;
    if (strcmp(lower_name, "abs") == 0) return OP_ABS;
    if (strcmp(lower_name, "ceil") == 0) return OP_CEIL;
    if (strcmp(lower_name, "floor") == 0) return OP_FLOOR;
    if (strcmp(lower_name, "round") == 0) return OP_ROUND;
    if (strcmp(lower_name, "fact") == 0 || strcmp(lower_name, "factorial") == 0) return OP_FACTORIAL;
    
    /* Unary trigonometric functions */
    if (strcmp(lower_name, "sin") == 0) return OP_SIN;
    if (strcmp(lower_name, "cos") == 0) return OP_COS;
    if (strcmp(lower_name, "tan") == 0) return OP_TAN;
    if (strcmp(lower_name, "asin") == 0 || strcmp(lower_name, "arcsin") == 0) return OP_ASIN;
    if (strcmp(lower_name, "acos") == 0 || strcmp(lower_name, "arccos") == 0) return OP_ACOS;
    if (strcmp(lower_name, "atan") == 0 || strcmp(lower_name, "arctan") == 0) return OP_ATAN;
    
    /* Unary hyperbolic functions */
    if (strcmp(lower_name, "sinh") == 0) return OP_SINH;
    if (strcmp(lower_name, "cosh") == 0) return OP_COSH;
    if (strcmp(lower_name, "tanh") == 0) return OP_TANH;
    
    /* Unary exponential and logarithmic functions */
    if (strcmp(lower_name, "exp") == 0) return OP_EXP;
    if (strcmp(lower_name, "ln") == 0 || strcmp(lower_name, "log") == 0) return OP_LOG;
    if (strcmp(lower_name, "log10") == 0) return OP_LOG10;
    if (strcmp(lower_name, "log2") == 0) return OP_LOG2;
    
    return OP_INVALID;
}

/**
 * @brief Get operation name string
 */
const char *get_operation_name(OperationType op) {
    switch (op) {
        case OP_ADD:         return "Addition";
        case OP_SUBTRACT:    return "Subtraction";
        case OP_MULTIPLY:    return "Multiplication";
        case OP_DIVIDE:      return "Division";
        case OP_POWER:       return "Power";
        case OP_MODULO:      return "Modulo";
        case OP_SQRT:        return "Square Root";
        case OP_CBRT:        return "Cube Root";
        case OP_SIN:         return "Sine";
        case OP_COS:         return "Cosine";
        case OP_TAN:         return "Tangent";
        case OP_ASIN:        return "Arc Sine";
        case OP_ACOS:        return "Arc Cosine";
        case OP_ATAN:        return "Arc Tangent";
        case OP_SINH:        return "Hyperbolic Sine";
        case OP_COSH:        return "Hyperbolic Cosine";
        case OP_TANH:        return "Hyperbolic Tangent";
        case OP_EXP:         return "Exponential";
        case OP_LOG:         return "Natural Logarithm";
        case OP_LOG10:       return "Base-10 Logarithm";
        case OP_LOG2:        return "Base-2 Logarithm";
        case OP_FACTORIAL:   return "Factorial";
        case OP_ABS:         return "Absolute Value";
        case OP_CEIL:        return "Ceiling";
        case OP_FLOOR:       return "Floor";
        case OP_ROUND:       return "Round";
        case OP_INVALID:     return "Invalid Operation";
        default:             return "Unknown";
    }
}

/**
 * @brief Check if operation is binary (requires 2 operands)
 */
bool is_binary_operation(OperationType op) {
    switch (op) {
        case OP_ADD:
        case OP_SUBTRACT:
        case OP_MULTIPLY:
        case OP_DIVIDE:
        case OP_POWER:
        case OP_MODULO:
            return true;
        default:
            return false;
    }
}