#include "calculator.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/* ==================== BASIC ARITHMETIC OPERATIONS ==================== */

/**
 * Adds two numbers
 * @param num1 First number
 * @param num2 Second number
 * @return Sum of num1 and num2
 */
double add(double num1, double num2) {
    return num1 + num2;
}

/**
 * Subtracts two numbers
 * @param num1 First number
 * @param num2 Second number to subtract
 * @return Difference (num1 - num2)
 */
double subtract(double num1, double num2) {
    return num1 - num2;
}

/**
 * Multiplies two numbers
 * @param num1 First number
 * @param num2 Second number
 * @return Product of num1 and num2
 */
double multiply(double num1, double num2) {
    return num1 * num2;
}

/**
 * Divides two numbers with error handling
 * @param num1 Dividend
 * @param num2 Divisor
 * @param error Pointer to error code (set to ERROR_DIV_ZERO if division by zero)
 * @return Result of num1 / num2, or 0 if error occurs
 */
double divide(double num1, double num2, int *error) {
    if (num2 == 0) {
        *error = ERROR_DIV_ZERO;
        return 0;
    }
    *error = SUCCESS;
    return num1 / num2;
}

/**
 * Raises num1 to the power of num2
 * @param num1 Base
 * @param num2 Exponent
 * @return num1 raised to the power of num2
 */
double power(double num1, double num2) {
    return pow(num1, num2);
}

/* ==================== SCIENTIFIC OPERATIONS ==================== */

/**
 * Calculates square root with error handling
 * @param num Number to find square root of
 * @param error Pointer to error code (set to ERROR_INVALID_INPUT for negative numbers)
 * @return Square root of num, or 0 if error occurs
 */
double square_root(double num, int *error) {
    if (num < 0) {
        *error = ERROR_INVALID_INPUT;
        return 0;
    }
    *error = SUCCESS;
    return sqrt(num);
}

/**
 * Calculates sine of a number (in radians)
 * @param num Angle in radians
 * @return Sine of num
 */
double sine(double num) {
    return sin(num);
}

/**
 * Calculates cosine of a number (in radians)
 * @param num Angle in radians
 * @return Cosine of num
 */
double cosine(double num) {
    return cos(num);
}

/**
 * Calculates tangent of a number (in radians)
 * @param num Angle in radians
 * @return Tangent of num
 */
double tangent(double num) {
    return tan(num);
}

/**
 * Calculates natural logarithm with error handling
 * @param num Number to find logarithm of
 * @param error Pointer to error code (set to ERROR_INVALID_INPUT for non-positive numbers)
 * @return Natural logarithm of num, or 0 if error occurs
 */
double logarithm(double num, int *error) {
    if (num <= 0) {
        *error = ERROR_INVALID_INPUT;
        return 0;
    }
    *error = SUCCESS;
    return log(num);
}

/**
 * Calculates factorial with error handling
 * @param num Number to find factorial of
 * @param error Pointer to error code (set to ERROR_INVALID_INPUT for negative or very large numbers)
 * @return Factorial of num, or 0 if error occurs
 */
double factorial(int num, int *error) {
    if (num < 0) {
        *error = ERROR_INVALID_INPUT;
        return 0;
    }
    if (num > 20) {  /* Prevent overflow */
        *error = ERROR_INVALID_INPUT;
        return 0;
    }
    
    *error = SUCCESS;
    double result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }
    return result;
}

/* ==================== UTILITY FUNCTIONS ==================== */

/**
 * Validates if a character is a valid operator
 * @param op Character to validate
 * @return 1 if valid, 0 if invalid
 */
int is_valid_operator(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^');
}

/**
 * Prints the main menu options
 */
void print_menu(void) {
    printf("\n");
    printf("=== SciCalc - Scientific Calculator ===\n");
    printf("Basic Operations:\n");
    printf("  + : Addition\n");
    printf("  - : Subtraction\n");
    printf("  * : Multiplication\n");
    printf("  / : Division\n");
    printf("  ^ : Power\n");
    printf("Advanced Options:\n");
    printf("  s : Scientific Operations\n");
    printf("  h : Show History\n");
    printf("  q : Quit\n");
    printf("====================================\n");
}

/**
 * Prints the scientific operations menu
 */
void print_scientific_menu(void) {
    printf("\n");
    printf("=== Scientific Operations ===\n");
    printf("  sqrt : Square Root\n");
    printf("  sin  : Sine (in radians)\n");
    printf("  cos  : Cosine (in radians)\n");
    printf("  tan  : Tangent (in radians)\n");
    printf("  log  : Natural Logarithm\n");
    printf("  fact : Factorial\n");
    printf("  back : Return to Main Menu\n");
    printf("=============================\n");
}

/**
 * Prints error messages based on error code
 * @param error_code Error code to print message for
 */
void print_error_message(int error_code) {
    switch (error_code) {
        case ERROR_DIV_ZERO:
            printf("Error: Division by zero is not allowed!\n");
            break;
        case ERROR_INVALID_OP:
            printf("Error: Invalid operator! Please enter a valid operator.\n");
            break;
        case ERROR_INVALID_INPUT:
            printf("Error: Invalid input for this operation!\n");
            break;
        default:
            printf("Error: Unknown error occurred!\n");
    }
}

/**
 * Adds a calculation to history
 * @param history Array to store history
 * @param history_count Pointer to current history count
 * @param operation Operation string
 * @param result Result of the operation
 */
void add_to_history(HistoryEntry *history, int *history_count, const char *operation, double result) {
    if (*history_count < MAX_HISTORY) {
        strncpy(history[*history_count].operation, operation, BUFFER_SIZE - 1);
        history[*history_count].operation[BUFFER_SIZE - 1] = '\0';
        history[*history_count].result = result;
        (*history_count)++;
    }
}

/**
 * Prints calculation history
 * @param history Array containing history
 * @param history_count Number of history entries
 */
void print_history(HistoryEntry *history, int history_count) {
    if (history_count == 0) {
        printf("No calculation history available.\n");
        return;
    }
    
    printf("\n=== Calculation History ===\n");
    for (int i = 0; i < history_count; i++) {
        printf("%d. %s = %.*f\n", i + 1, history[i].operation, PRECISION, history[i].result);
    }
    printf("===========================\n");
}
