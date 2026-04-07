#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/**
 * @file functions.h
 * @brief Mathematical functions library
 */

#define PI 3.14159265358979323846
#define E 2.71828182845904523536
#define GOLDEN_RATIO 1.61803398874989484820

/**
 * Basic arithmetic operations
 */
double func_add(double a, double b);
double func_subtract(double a, double b);
double func_multiply(double a, double b);
double func_divide(double a, double b);
double func_power(double base, double exponent);
double func_modulo(double a, double b);

/**
 * Trigonometric functions (input in radians)
 */
double func_sin(double x);
double func_cos(double x);
double func_tan(double x);
double func_asin(double x);
double func_acos(double x);
double func_atan(double x);

/**
 * Logarithmic and exponential functions
 */
double func_ln(double x);
double func_log10(double x);
double func_log2(double x);
double func_exp(double x);

/**
 * Other mathematical functions
 */
double func_sqrt(double x);
double func_cbrt(double x);
double func_abs(double x);
double func_factorial(double x);
double func_floor(double x);
double func_ceil(double x);
double func_round(double x);

/**
 * Statistical functions
 */
double func_mean(double* values, int count);
double func_median(double* values, int count);
double func_std_dev(double* values, int count);

/**
 * Combinatorics
 */
double func_factorial_calc(int n);
double func_combination(int n, int k);
double func_permutation(int n, int k);

/**
 * Degree to radian conversion
 */
double deg_to_rad(double degrees);
double rad_to_deg(double radians);

#endif // FUNCTIONS_H
