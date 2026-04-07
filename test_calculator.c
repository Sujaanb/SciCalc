#include <stdio.h>
#include <math.h>
#include "calculator.h"

/**
 * Simple unit tests for calculator functions
 * Compile with: gcc -Wall -Wextra -std=c99 -o test_calculator test_calculator.c calculator.c -lm
 * Run with: ./test_calculator
 */

#define EPSILON 0.0001
#define PASS "\033[0;32mPASS\033[0m"
#define FAIL "\033[0;31mFAIL\033[0m"

int tests_passed = 0;
int tests_failed = 0;

/**
 * Compare two doubles with tolerance for floating-point errors
 */
int assert_double_equals(double expected, double actual, const char *test_name) {
    if (fabs(expected - actual) < EPSILON) {
        printf("[%s] %s\n", PASS, test_name);
        tests_passed++;
        return 1;
    } else {
        printf("[%s] %s (expected: %.4f, got: %.4f)\n", FAIL, test_name, expected, actual);
        tests_failed++;
        return 0;
    }
}

/**
 * Assert that an error code is as expected
 */
int assert_error_code(int expected, int actual, const char *test_name) {
    if (expected == actual) {
        printf("[%s] %s\n", PASS, test_name);
        tests_passed++;
        return 1;
    } else {
        printf("[%s] %s (expected error: %d, got: %d)\n", FAIL, test_name, expected, actual);
        tests_failed++;
        return 0;
    }
}

/**
 * Test basic arithmetic operations
 */
void test_arithmetic(void) {
    printf("\n=== Testing Arithmetic Operations ===\n");
    
    assert_double_equals(15.0, add(10.0, 5.0), "Addition: 10 + 5 = 15");
    assert_double_equals(5.0, subtract(10.0, 5.0), "Subtraction: 10 - 5 = 5");
    assert_double_equals(50.0, multiply(10.0, 5.0), "Multiplication: 10 * 5 = 50");
    assert_double_equals(2.0, divide(10.0, 5.0, &(int){0}), "Division: 10 / 5 = 2");
    assert_double_equals(8.0, power(2.0, 3.0), "Power: 2 ^ 3 = 8");
}

/**
 * Test division by zero error handling
 */
void test_division_by_zero(void) {
    printf("\n=== Testing Division by Zero ===\n");
    
    int error;
    divide(10.0, 0.0, &error);
    assert_error_code(ERROR_DIV_ZERO, error, "Division by zero should set ERROR_DIV_ZERO");
    
    int no_error;
    divide(10.0, 2.0, &no_error);
    assert_error_code(SUCCESS, no_error, "Valid division should not set error");
}

/**
 * Test scientific operations
 */
void test_scientific(void) {
    printf("\n=== Testing Scientific Operations ===\n");
    
    int error;
    
    assert_double_equals(3.0, square_root(9.0, &error), "Square root: sqrt(9) = 3");
    assert_double_equals(0.0, sine(0.0), "Sine: sin(0) = 0");
    assert_double_equals(1.0, cosine(0.0), "Cosine: cos(0) = 1");
    
    double log_result = logarithm(2.718281828, &error);
    assert_double_equals(1.0, log_result, "Logarithm: ln(e) ≈ 1");
    
    assert_double_equals(120.0, factorial(5, &error), "Factorial: 5! = 120");
    assert_double_equals(1.0, factorial(0, &error), "Factorial: 0! = 1");
    assert_double_equals(1.0, factorial(1, &error), "Factorial: 1! = 1");
}

/**
 * Test error handling for scientific operations
 */
void test_scientific_errors(void) {
    printf("\n=== Testing Scientific Operation Errors ===\n");
    
    int error;
    
    square_root(-1.0, &error);
    assert_error_code(ERROR_INVALID_INPUT, error, "Square root of negative should set ERROR_INVALID_INPUT");
    
    logarithm(-5.0, &error);
    assert_error_code(ERROR_INVALID_INPUT, error, "Logarithm of negative should set ERROR_INVALID_INPUT");
    
    logarithm(0.0, &error);
    assert_error_code(ERROR_INVALID_INPUT, error, "Logarithm of zero should set ERROR_INVALID_INPUT");
    
    factorial(-5, &error);
    assert_error_code(ERROR_INVALID_INPUT, error, "Factorial of negative should set ERROR_INVALID_INPUT");
    
    factorial(21, &error);
    assert_error_code(ERROR_INVALID_INPUT, error, "Factorial > 20 should set ERROR_INVALID_INPUT");
}

/**
 * Test operator validation
 */
void test_operator_validation(void) {
    printf("\n=== Testing Operator Validation ===\n");
    
    if (is_valid_operator('+')) {
        printf("[%s] '+' is a valid operator\n", PASS);
        tests_passed++;
    } else {
        printf("[%s] '+' should be a valid operator\n", FAIL);
        tests_failed++;
    }
    
    if (is_valid_operator('-')) {
        printf("[%s] '-' is a valid operator\n", PASS);
        tests_passed++;
    } else {
        printf("[%s] '-' should be a valid operator\n", FAIL);
        tests_failed++;
    }
    
    if (!is_valid_operator('x')) {
        printf("[%s] 'x' is not a valid operator\n", PASS);
        tests_passed++;
    } else {
        printf("[%s] 'x' should not be a valid operator\n", FAIL);
        tests_failed++;
    }
}

/**
 * Print test summary
 */
void print_test_summary(void) {
    printf("\n");
    printf("╔════════════════════════════════════╗\n");
    printf("║        Test Summary                ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║ Tests Passed: %d                   ║\n", tests_passed);
    printf("║ Tests Failed: %d                   ║\n", tests_failed);
    printf("║ Total Tests:  %d                   ║\n", tests_passed + tests_failed);
    printf("╚════════════════════════════════════╝\n");
    printf("\n");
}

/**
 * Main test runner
 */
int main(void) {
    printf("\n");
    printf("╔════════════════════════════════════╗\n");
    printf("║     SciCalc Test Suite             ║\n");
    printf("╚════════════════════════════════════╝\n");
    
    test_arithmetic();
    test_division_by_zero();
    test_scientific();
    test_scientific_errors();
    test_operator_validation();
    
    print_test_summary();
    
    return (tests_failed == 0) ? 0 : 1;
}
