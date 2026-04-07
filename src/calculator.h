#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdbool.h>

/**
 * @file calculator.h
 * @brief Main calculator engine
 */

#define MAX_EXPRESSION 256
#define MAX_HISTORY 100

/**
 * Calculator state structure
 */
typedef struct {
    double last_result;
    int precision;
    bool show_history;
    int history_count;
} Calculator;

/**
 * Initialize calculator
 */
Calculator* calculator_new(void);

/**
 * Free calculator resources
 */
void calculator_free(Calculator* calc);

/**
 * Evaluate a mathematical expression
 * @param calc Calculator instance
 * @param expression Expression string to evaluate
 * @param result Output for the result
 * @return true if evaluation was successful
 */
bool calculator_evaluate(Calculator* calc, const char* expression, double* result);

/**
 * Set precision for output
 */
void calculator_set_precision(Calculator* calc, int precision);

/**
 * Get last result
 */
double calculator_get_last_result(Calculator* calc);

#endif // CALCULATOR_H
