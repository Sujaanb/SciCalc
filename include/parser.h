/**
 * @file parser.h
 * @brief Expression parser header for handling user input
 * @author Sujaan Bhattacharyya
 * @version 1.0.0
 */

#ifndef PARSER_H
#define PARSER_H

#include "calculator.h"
#include <stdbool.h>

/**
 * @enum OperationType
 * @brief Types of operations supported
 */
typedef enum {
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_POWER,
    OP_MODULO,
    OP_SQRT,
    OP_CBRT,
    OP_SIN,
    OP_COS,
    OP_TAN,
    OP_ASIN,
    OP_ACOS,
    OP_ATAN,
    OP_SINH,
    OP_COSH,
    OP_TANH,
    OP_EXP,
    OP_LOG,
    OP_LOG10,
    OP_LOG2,
    OP_FACTORIAL,
    OP_ABS,
    OP_CEIL,
    OP_FLOOR,
    OP_ROUND,
    OP_INVALID
} OperationType;

/**
 * @struct ParsedExpression
 * @brief Parsed expression structure
 */
typedef struct {
    OperationType operation;      /**< Operation type */
    double operand1;              /**< First operand */
    double operand2;              /**< Second operand (if needed) */
    bool has_second_operand;      /**< Whether second operand is valid */
    ErrorCode parse_error;        /**< Parse error if any */
} ParsedExpression;

/**
 * @brief Parse operator character to operation type
 * @param op Operator character
 * @return OperationType
 */
OperationType parse_operator(char op);

/**
 * @brief Parse function name string to operation type
 * @param func_name Function name
 * @return OperationType
 */
OperationType parse_function(const char *func_name);

/**
 * @brief Get operation name string
 * @param op Operation type
 * @return Operation name string
 */
const char *get_operation_name(OperationType op);

/**
 * @brief Check if operation is binary (requires 2 operands)
 * @param op Operation type
 * @return true if binary, false if unary
 */
bool is_binary_operation(OperationType op);

#endif /* PARSER_H */