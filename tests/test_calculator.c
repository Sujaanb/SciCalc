/**
 * @file test_calculator.c
 * @brief Unit tests for SciCalc calculator functions
 * @author Sujaan Bhattacharyya
 * @version 1.0.0
 */

#include "../include/calculator.h"
#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EPSILON 1e-10
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

/* Test statistics */
static int tests_passed = 0;
static int tests_failed = 0;

/* Test helper macros */
#define ASSERT_EQUAL(actual, expected, tolerance) \
    do { \
        if (fabs((actual) - (expected)) <= (tolerance)) { \
            printf(GREEN "  ✓ PASS" RESET "\n"); \
            tests_passed++; \
        } else { \
            printf(RED "  ✗ FAIL" RESET " - Expected: %g, Got: %g\n", (expected), (actual)); \
            tests_failed++; \
        } \
    } while(0)

#define ASSERT_ERROR(result, error_code) \
    do { \
        if ((result).error == (error_code)) { \
            printf(GREEN "  ✓ PASS" RESET "\n"); \
            tests_passed++; \
        } else { \
            printf(RED "  ✗ FAIL" RESET " - Expected error: %d, Got: %d\n", (error_code), (result).error); \
            tests_failed++; \
        } \
    } while(0)

/* ============= Test Functions ============= */

void test_basic_operations(void) {
    printf("\n=== Testing Basic Operations ==="\n");
    
    /* Addition */
    printf("  Testing: 5 + 3 = 8");
    CalculationResult result = calc_add(5.0, 3.0);
    ASSERT_EQUAL(result.value, 8.0, EPSILON);
    
    /* Subtraction */
    printf("  Testing: 10 - 4 = 6");
    result = calc_subtract(10.0, 4.0);
    ASSERT_EQUAL(result.value, 6.0, EPSILON);
    
    /* Multiplication */
    printf("  Testing: 3 * 7 = 21");
    result = calc_multiply(3.0, 7.0);
    ASSERT_EQUAL(result.value, 21.0, EPSILON);
    
    /* Division */
    printf("  Testing: 20 / 4 = 5");
    result = calc_divide(20.0, 4.0);
    ASSERT_EQUAL(result.value, 5.0, EPSILON);
    
    /* Power */
    printf("  Testing: 2 ^ 3 = 8");
    result = calc_power(2.0, 3.0);
    ASSERT_EQUAL(result.value, 8.0, EPSILON);
    
    /* Modulo */
    printf("  Testing: 10 %% 3 = 1");
    result = calc_modulo(10.0, 3.0);
    ASSERT_EQUAL(result.value, 1.0, EPSILON);
}

void test_error_handling(void) {
    printf("\n=== Testing Error Handling ==="\n");
    
    /* Division by zero */
    printf("  Testing: 10 / 0 = Error");
    CalculationResult result = calc_divide(10.0, 0.0);
    ASSERT_ERROR(result, ERR_DIV_ZERO);
    
    /* Square root of negative */
    printf("  Testing: sqrt(-1) = Error");
    result = calc_sqrt(-1.0);
    ASSERT_ERROR(result, ERR_DOMAIN);
    
    /* Arc sine out of range */
    printf("  Testing: asin(2) = Error");
    result = calc_asin(2.0);
    ASSERT_ERROR(result, ERR_DOMAIN);
    
    /* Negative factorial */
    printf("  Testing: fact(-5) = Error");
    result = calc_factorial(-5.0);
    ASSERT_ERROR(result, ERR_DOMAIN);
    
    /* Log of zero */
    printf("  Testing: log(0) = Error");
    result = calc_log(0.0);
    ASSERT_ERROR(result, ERR_DOMAIN);
}

void test_algebraic_functions(void) {
    printf("\n=== Testing Algebraic Functions ==="\n");
    
    /* Square root */
    printf("  Testing: sqrt(16) = 4");
    CalculationResult result = calc_sqrt(16.0);
    ASSERT_EQUAL(result.value, 4.0, EPSILON);
    
    /* Cube root */
    printf("  Testing: cbrt(27) = 3");
    result = calc_cbrt(27.0);
    ASSERT_EQUAL(result.value, 3.0, EPSILON);
    
    /* Absolute value */
    printf("  Testing: abs(-5) = 5");
    result = calc_abs(-5.0);
    ASSERT_EQUAL(result.value, 5.0, EPSILON);
    
    /* Ceiling */
    printf("  Testing: ceil(3.2) = 4");
    result = calc_ceil(3.2);
    ASSERT_EQUAL(result.value, 4.0, EPSILON);
    
    /* Floor */
    printf("  Testing: floor(3.7) = 3");
    result = calc_floor(3.7);
    ASSERT_EQUAL(result.value, 3.0, EPSILON);
    
    /* Factorial */
    printf("  Testing: fact(5) = 120");
    result = calc_factorial(5.0);
    ASSERT_EQUAL(result.value, 120.0, EPSILON);
}

void test_trigonometric_functions(void) {
    printf("\n=== Testing Trigonometric Functions ==="\n");
    
    /* Sine at 0 */
    printf("  Testing: sin(0) = 0");
    CalculationResult result = calc_sin(0.0);
    ASSERT_EQUAL(result.value, 0.0, EPSILON);
    
    /* Cosine at 0 */
    printf("  Testing: cos(0) = 1");
    result = calc_cos(0.0);
    ASSERT_EQUAL(result.value, 1.0, EPSILON);
    
    /* Arc sine at 0 */
    printf("  Testing: asin(0) = 0");
    result = calc_asin(0.0);
    ASSERT_EQUAL(result.value, 0.0, EPSILON);
    
    /* Arc cosine at 1 */
    printf("  Testing: acos(1) = 0");
    result = calc_acos(1.0);
    ASSERT_EQUAL(result.value, 0.0, EPSILON);
}

void test_exponential_logarithmic(void) {
    printf("\n=== Testing Exponential & Logarithmic ==="\n");
    
    /* Exponential */
    printf("  Testing: exp(0) = 1");
    CalculationResult result = calc_exp(0.0);
    ASSERT_EQUAL(result.value, 1.0, EPSILON);
    
    /* Natural log */
    printf("  Testing: log(1) = 0");
    result = calc_log(1.0);
    ASSERT_EQUAL(result.value, 0.0, EPSILON);
    
    /* Base 10 log */
    printf("  Testing: log10(100) = 2");
    result = calc_log10(100.0);
    ASSERT_EQUAL(result.value, 2.0, EPSILON);
    
    /* Base 2 log */
    printf("  Testing: log2(8) = 3");
    result = calc_log2(8.0);
    ASSERT_EQUAL(result.value, 3.0, EPSILON);
}

void test_parser(void) {
    printf("\n=== Testing Parser ==="\n");
    
    /* Parse operators */
    printf("  Testing: parse_operator('+') = OP_ADD");
    OperationType op = parse_operator('+');
    if (op == OP_ADD) {
        printf(GREEN "  ✓ PASS" RESET "\n");
        tests_passed++;
    } else {
        printf(RED "  ✗ FAIL" RESET "\n");
        tests_failed++;
    }
    
    printf("  Testing: is_binary_operation(OP_ADD) = true");
    bool is_binary = is_binary_operation(OP_ADD);
    if (is_binary) {
        printf(GREEN "  ✓ PASS" RESET "\n");
        tests_passed++;
    } else {
        printf(RED "  ✗ FAIL" RESET "\n");
        tests_failed++;
    }
    
    printf("  Testing: is_binary_operation(OP_SQRT) = false");
    is_binary = is_binary_operation(OP_SQRT);
    if (!is_binary) {
        printf(GREEN "  ✓ PASS" RESET "\n");
        tests_passed++;
    } else {
        printf(RED "  ✗ FAIL" RESET "\n");
        tests_failed++;
    }
}

void test_input_validation(void) {
    printf("\n=== Testing Input Validation ==="\n");
    
    double value = 0.0;
    
    /* Valid number */
    printf("  Testing: is_valid_number(\"3.14\")");
    bool valid = is_valid_number("3.14", &value);
    if (valid && fabs(value - 3.14) < 0.01) {
        printf(GREEN "  ✓ PASS" RESET "\n");
        tests_passed++;
    } else {
        printf(RED "  ✗ FAIL" RESET "\n");
        tests_failed++;
    }
    
    /* Invalid number */
    printf("  Testing: is_valid_number(\"abc\") = false");
    valid = is_valid_number("abc", &value);
    if (!valid) {
        printf(GREEN "  ✓ PASS" RESET "\n");
        tests_passed++;
    } else {
        printf(RED "  ✗ FAIL" RESET "\n");
        tests_failed++;
    }
    
    /* Empty string */
    printf("  Testing: is_valid_number(\"\")");
    valid = is_valid_number("", &value);
    if (!valid) {
        printf(GREEN "  ✓ PASS" RESET "\n");
        tests_passed++;
    } else {
        printf(RED "  ✗ FAIL" RESET "\n");
        tests_failed++;
    }
}

int main(void) {
    printf("\n");
    printf("\033[1m========================================\033[0m\n");
    printf("\033[1m   SciCalc Unit Test Suite v1.0.0       \033[0m\n");
    printf("\033[1m========================================\033[0m\n");
    
    test_basic_operations();
    test_error_handling();
    test_algebraic_functions();
    test_trigonometric_functions();
    test_exponential_logarithmic();
    test_parser();
    test_input_validation();
    
    printf("\n");
    printf("\033[1m========================================\033[0m\n");
    printf("\033[1m              TEST RESULTS               \033[0m\n");
    printf("\033[1m========================================\033[0m\n");
    printf(GREEN "✓ Tests Passed: %d" RESET "\n", tests_passed);
    printf(RED "✗ Tests Failed: %d" RESET "\n", tests_failed);
    printf("Total Tests: %d\n", tests_passed + tests_failed);
    printf("Coverage: %.1f%%\n", (tests_passed * 100.0) / (tests_passed + tests_failed));
    printf("\033[1m========================================\033[0m\n\n");
    
    return (tests_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}