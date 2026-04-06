/**
 * @file calculator.c
 * @brief Core calculator implementation with all mathematical operations
 * @author Sujaan Bhattacharyya
 * @version 1.0.0
 */

#include "../include/calculator.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

/* Private helper to check for NaN or Inf */
static bool is_valid_result(double value) {
    return !isnan(value) && !isinf(value);
}

/* Private helper to create result */
static CalculationResult create_result(double value, ErrorCode error, const char *msg) {
    CalculationResult result;
    result.value = value;
    result.error = error;
    if (msg) {
        strncpy(result.error_message, msg, sizeof(result.error_message) - 1);
        result.error_message[sizeof(result.error_message) - 1] = '\0';
    } else {
        result.error_message[0] = '\0';
    }
    return result;
}

/* ============== Basic Operations ============== */

/**
 * @brief Add two numbers
 */
CalculationResult calc_add(double num1, double num2) {
    double result = num1 + num2;
    
    if (fabs(result) > DBL_MAX) {
        return create_result(0, ERR_OVERFLOW, "Addition result overflow");
    }
    
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Subtract two numbers
 */
CalculationResult calc_subtract(double num1, double num2) {
    double result = num1 - num2;
    
    if (fabs(result) > DBL_MAX) {
        return create_result(0, ERR_OVERFLOW, "Subtraction result overflow");
    }
    
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Multiply two numbers
 */
CalculationResult calc_multiply(double num1, double num2) {
    double result = num1 * num2;
    
    if (fabs(result) > DBL_MAX && !(num1 == 0 || num2 == 0)) {
        return create_result(0, ERR_OVERFLOW, "Multiplication result overflow");
    }
    
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Divide two numbers with zero-division check
 */
CalculationResult calc_divide(double num1, double num2) {
    if (num2 == 0.0) {
        return create_result(0, ERR_DIV_ZERO, "Division by zero");
    }
    
    double result = num1 / num2;
    
    if (!is_valid_result(result)) {
        return create_result(0, ERR_OVERFLOW, "Division result invalid");
    }
    
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate power
 */
CalculationResult calc_power(double num1, double num2) {
    /* Check for domain errors */
    if (num1 < 0 && floor(num2) != num2) {
        return create_result(0, ERR_DOMAIN, "Negative number to non-integer power");
    }
    
    double result = pow(num1, num2);
    
    if (!is_valid_result(result)) {
        return create_result(0, ERR_OVERFLOW, "Power operation resulted in overflow");
    }
    
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate modulo
 */
CalculationResult calc_modulo(double num1, double num2) {
    if (num2 == 0.0) {
        return create_result(0, ERR_DIV_ZERO, "Modulo by zero");
    }
    
    if (floor(num1) != num1 || floor(num2) != num2) {
        return create_result(0, ERR_DOMAIN, "Modulo requires integer operands");
    }
    
    double result = fmod(num1, num2);
    
    return create_result(result, ERR_SUCCESS, NULL);
}

/* ============== Scientific Functions - Algebraic ============== */

/**
 * @brief Calculate square root
 */
CalculationResult calc_sqrt(double num) {
    if (num < 0) {
        return create_result(0, ERR_DOMAIN, "Square root of negative number");
    }
    
    double result = sqrt(num);
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate cube root
 */
CalculationResult calc_cbrt(double num) {
    double result = cbrt(num);
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate factorial
 */
CalculationResult calc_factorial(double num) {
    if (num < 0 || floor(num) != num) {
        return create_result(0, ERR_DOMAIN, "Factorial requires non-negative integer");
    }
    
    if (num > 170) {
        return create_result(0, ERR_OVERFLOW, "Factorial overflow (max 170)");
    }
    
    double result = 1.0;
    for (int i = 2; i <= (int)num; i++) {
        result *= i;
    }
    
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate absolute value
 */
CalculationResult calc_abs(double num) {
    return create_result(fabs(num), ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate ceiling
 */
CalculationResult calc_ceil(double num) {
    return create_result(ceil(num), ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate floor
 */
CalculationResult calc_floor(double num) {
    return create_result(floor(num), ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate rounded value
 */
CalculationResult calc_round(double num) {
    return create_result(round(num), ERR_SUCCESS, NULL);
}

/* ============== Scientific Functions - Trigonometric ============== */

/**
 * @brief Calculate sine (in radians)
 */
CalculationResult calc_sin(double num) {
    double result = sin(num);
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate cosine (in radians)
 */
CalculationResult calc_cos(double num) {
    double result = cos(num);
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate tangent (in radians)
 */
CalculationResult calc_tan(double num) {
    double result = tan(num);
    
    /* Check for undefined points */
    if (!is_valid_result(result)) {
        return create_result(0, ERR_DOMAIN, "Tangent undefined at this point");
    }
    
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate arc sine
 */
CalculationResult calc_asin(double num) {
    if (num < -1.0 || num > 1.0) {
        return create_result(0, ERR_DOMAIN, "Arc sine requires value between -1 and 1");
    }
    
    double result = asin(num);
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate arc cosine
 */
CalculationResult calc_acos(double num) {
    if (num < -1.0 || num > 1.0) {
        return create_result(0, ERR_DOMAIN, "Arc cosine requires value between -1 and 1");
    }
    
    double result = acos(num);
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate arc tangent
 */
CalculationResult calc_atan(double num) {
    double result = atan(num);
    return create_result(result, ERR_SUCCESS, NULL);
}

/* ============== Scientific Functions - Hyperbolic ============== */

/**
 * @brief Calculate hyperbolic sine
 */
CalculationResult calc_sinh(double num) {
    double result = sinh(num);
    
    if (!is_valid_result(result)) {
        return create_result(0, ERR_OVERFLOW, "Hyperbolic sine overflow");
    }
    
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate hyperbolic cosine
 */
CalculationResult calc_cosh(double num) {
    double result = cosh(num);
    
    if (!is_valid_result(result)) {
        return create_result(0, ERR_OVERFLOW, "Hyperbolic cosine overflow");
    }
    
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate hyperbolic tangent
 */
CalculationResult calc_tanh(double num) {
    double result = tanh(num);
    return create_result(result, ERR_SUCCESS, NULL);
}

/* ============== Scientific Functions - Exponential & Logarithmic ============== */

/**
 * @brief Calculate exponential (e^x)
 */
CalculationResult calc_exp(double num) {
    double result = exp(num);
    
    if (!is_valid_result(result)) {
        return create_result(0, ERR_OVERFLOW, "Exponential overflow");
    }
    
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate natural logarithm
 */
CalculationResult calc_log(double num) {
    if (num <= 0) {
        return create_result(0, ERR_DOMAIN, "Natural logarithm requires positive number");
    }
    
    double result = log(num);
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate base-10 logarithm
 */
CalculationResult calc_log10(double num) {
    if (num <= 0) {
        return create_result(0, ERR_DOMAIN, "Base-10 logarithm requires positive number");
    }
    
    double result = log10(num);
    return create_result(result, ERR_SUCCESS, NULL);
}

/**
 * @brief Calculate base-2 logarithm
 */
CalculationResult calc_log2(double num) {
    if (num <= 0) {
        return create_result(0, ERR_DOMAIN, "Base-2 logarithm requires positive number");
    }
    
    double result = log2(num);
    return create_result(result, ERR_SUCCESS, NULL);
}

/* ============== Utility Functions ============== */

/**
 * @brief Validate if string is a valid number
 */
bool is_valid_number(const char *str, double *result) {
    if (!str || str[0] == '\0') {
        return false;
    }
    
    char *endptr;
    double value = strtod(str, &endptr);
    
    /* Check if entire string was consumed */
    if (*endptr != '\0') {
        return false;
    }
    
    /* Check for valid range */
    if (value == HUGE_VAL || value == -HUGE_VAL) {
        return false;
    }
    
    if (result) {
        *result = value;
    }
    
    return true;
}

/**
 * @brief Get human-readable error message
 */
const char *get_error_message(ErrorCode error) {
    switch (error) {
        case ERR_SUCCESS:
            return "Operation successful";
        case ERR_INVALID_INPUT:
            return "Invalid input provided";
        case ERR_INVALID_OPERATOR:
            return "Invalid operator";
        case ERR_DIV_ZERO:
            return "Division by zero";
        case ERR_DOMAIN:
            return "Mathematical domain error";
        case ERR_OVERFLOW:
            return "Result overflow";
        case ERR_MEMORY:
            return "Memory allocation error";
        default:
            return "Unknown error";
    }
}

/**
 * @brief Print formatted result
 */
void print_result(CalculationResult result, const char *operation) {
    if (result.error != ERR_SUCCESS) {
        printf("❌ Error: %s\n", 
               result.error_message[0] != '\0' ? result.error_message : get_error_message(result.error));
    } else {
        printf("✓ %s = %.10g\n", operation, result.value);
    }
}