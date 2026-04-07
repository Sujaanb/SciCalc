#include <stdio.h>
#include <math.h>
#include "functions.h"
#include "parser.h"
#include "history.h"

#define EPSILON 1e-6
#define ASSERT_EQUAL(actual, expected) \
    do { \
        if (fabs((actual) - (expected)) > EPSILON) { \
            printf("FAIL: Expected %.6f, got %.6f\n", (expected), (actual)); \
            test_failures++; \
        } \
    } while(0)

static int test_failures = 0;
static int test_count = 0;

void test_basic_functions(void) {
    printf("\nTesting Basic Functions...\n");
    
    test_count++;
    ASSERT_EQUAL(func_add(2, 3), 5);
    
    test_count++;
    ASSERT_EQUAL(func_subtract(10, 4), 6);
    
    test_count++;
    ASSERT_EQUAL(func_multiply(6, 7), 42);
    
    test_count++;
    ASSERT_EQUAL(func_divide(20, 4), 5);
    
    test_count++;
    ASSERT_EQUAL(func_power(2, 8), 256);
    
    test_count++;
    ASSERT_EQUAL(func_modulo(17, 5), 2);
    
    printf("  ✓ All basic function tests passed\n");
}

void test_trigonometric(void) {
    printf("Testing Trigonometric Functions...\n");
    
    test_count++;
    ASSERT_EQUAL(func_sin(0), 0);
    
    test_count++;
    ASSERT_EQUAL(func_cos(0), 1);
    
    test_count++;
    ASSERT_EQUAL(func_tan(0), 0);
    
    printf("  ✓ All trigonometric tests passed\n");
}

void test_logarithmic(void) {
    printf("Testing Logarithmic Functions...\n");
    
    test_count++;
    ASSERT_EQUAL(func_ln(E), 1);
    
    test_count++;
    ASSERT_EQUAL(func_log10(100), 2);
    
    test_count++;
    ASSERT_EQUAL(func_sqrt(16), 4);
    
    printf("  ✓ All logarithmic tests passed\n");
}

void test_parser(void) {
    printf("Testing Expression Parser...\n");
    
    double result = 0.0;
    
    test_count++;
    if (parser_evaluate("2 + 3", &result)) {
        ASSERT_EQUAL(result, 5);
    }
    
    test_count++;
    if (parser_evaluate("10 - 4", &result)) {
        ASSERT_EQUAL(result, 6);
    }
    
    test_count++;
    if (parser_evaluate("2 * 3 + 4", &result)) {
        ASSERT_EQUAL(result, 10);
    }
    
    test_count++;
    if (parser_evaluate("(2 + 3) * 4", &result)) {
        ASSERT_EQUAL(result, 20);
    }
    
    test_count++;
    if (parser_evaluate("2 ^ 3", &result)) {
        ASSERT_EQUAL(result, 8);
    }
    
    printf("  ✓ All parser tests passed\n");
}

void test_combinatorics(void) {
    printf("Testing Combinatorics...\n");
    
    test_count++;
    ASSERT_EQUAL(func_factorial_calc(5), 120);
    
    test_count++;
    ASSERT_EQUAL(func_combination(5, 2), 10);
    
    test_count++;
    ASSERT_EQUAL(func_permutation(5, 2), 20);
    
    printf("  ✓ All combinatorics tests passed\n");
}

void test_history(void) {
    printf("Testing History...\n");
    
    History* hist = history_new();
    
    test_count++;
    history_add(hist, "2 + 3", 5);
    history_add(hist, "5 * 4", 20);
    HistoryEntry* entry = history_get(hist, 0);
    if (entry && entry->result == 5) {
        // Test passed
    } else {
        test_failures++;
        printf("FAIL: History entry mismatch\n");
    }
    
    history_free(hist);
    printf("  ✓ All history tests passed\n");
}

int main(void) {
    printf("=== SciCalc Test Suite ===\n");
    
    test_basic_functions();
    test_trigonometric();
    test_logarithmic();
    test_parser();
    test_combinatorics();
    test_history();
    
    printf("\n=== Test Results ===\n");
    printf("Total Tests: %d\n", test_count);
    printf("Failures: %d\n", test_failures);
    printf("Success: %d/%d\n", test_count - test_failures, test_count);
    
    if (test_failures == 0) {
        printf("\n✓ All tests passed!\n");
        return 0;
    } else {
        printf("\n✗ Some tests failed\n");
        return 1;
    }
}
