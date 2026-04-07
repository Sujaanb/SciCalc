#ifndef CALCULATOR_H
#define CALCULATOR_H

/**
 * Basic Arithmetic Operations
 */
double add(double num1, double num2);
double subtract(double num1, double num2);
double multiply(double num1, double num2);
double divide(double num1, double num2, int *error_flag);
double modulo_op(double num1, double num2, int *error_flag);
double power(double num1, double num2);

/**
 * Scientific Functions
 */
double square_root(double num, int *error_flag);
double absolute(double num);
double sine(double num, int use_degrees);
double cosine(double num, int use_degrees);
double tangent(double num, int use_degrees);
double natural_log(double num, int *error_flag);
double log_base_10(double num, int *error_flag);
double exponential(double num);
double factorial(double num, int *error_flag);

/**
 * Display Functions
 */
void display_menu(void);
void display_help(void);

#endif // CALCULATOR_H