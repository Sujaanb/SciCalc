/**
 * @file calculator.h
 * @brief Main calculator header with error codes and function declarations
 * @author Sujaan Bhattacharyya
 * @version 1.0.0
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdbool.h>

/**
 * @enum ErrorCode
 * @brief Error codes for calculator operations
 */
typedef enum {
    ERR_SUCCESS = 0,              /**< Operation successful */
    ERR_INVALID_INPUT = 1,        /**< Invalid input provided */
    ERR_INVALID_OPERATOR = 2,     /**< Invalid operator */
    ERR_DIV_ZERO = 3,             /**< Division by zero attempted */
    ERR_DOMAIN = 4,               /**< Mathematical domain error */
    ERR_OVERFLOW = 5,             /**< Result overflow */
    ERR_MEMORY = 6                /**< Memory allocation error */
} ErrorCode;

/**
 * @struct CalculationResult
 * @brief Result structure containing value and error information
 */
typedef struct {
    double value;                 /**< Calculation result */
    ErrorCode error;              /**< Error code if any */
    char error_message[256];      /**< Human-readable error message */
} CalculationResult;

/* Basic Operations */
CalculationResult calc_add(double num1, double num2);
CalculationResult calc_subtract(double num1, double num2);
CalculationResult calc_multiply(double num1, double num2);
CalculationResult calc_divide(double num1, double num2);
CalculationResult calc_power(double num1, double num2);
CalculationResult calc_modulo(double num1, double num2);

/* Scientific Functions */
CalculationResult calc_sqrt(double num);
CalculationResult calc_cbrt(double num);
CalculationResult calc_sin(double num);
CalculationResult calc_cos(double num);
CalculationResult calc_tan(double num);
CalculationResult calc_asin(double num);
CalculationResult calc_acos(double num);
CalculationResult calc_atan(double num);
CalculationResult calc_sinh(double num);
CalculationResult calc_cosh(double num);
CalculationResult calc_tanh(double num);
CalculationResult calc_exp(double num);
CalculationResult calc_log(double num);
CalculationResult calc_log10(double num);
CalculationResult calc_log2(double num);
CalculationResult calc_factorial(double num);
CalculationResult calc_abs(double num);
CalculationResult calc_ceil(double num);
CalculationResult calc_floor(double num);
CalculationResult calc_round(double num);

/* Utility Functions */
bool is_valid_number(const char *str, double *result);
const char *get_error_message(ErrorCode error);
void print_result(CalculationResult result, const char *operation);

#endif /* CALCULATOR_H */