#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "calculator.h"

/* ============================================================================
 * BASIC ARITHMETIC OPERATIONS
 * ============================================================================ */

/**
 * Adds two numbers
 */
double add(double num1, double num2) {
    return num1 + num2;
}

/**
 * Subtracts two numbers
 */
double subtract(double num1, double num2) {
    return num1 - num2;
}

/**
 * Multiplies two numbers
 */
double multiply(double num1, double num2) {
    return num1 * num2;
}

/**
 * Divides two numbers with error handling
 * Sets error_flag if division by zero is attempted
 */
double divide(double num1, double num2, int *error_flag) {
    if (num2 == 0) {
        *error_flag = 1;
        return 0;
    }
    *error_flag = 0;
    return num1 / num2;
}

/**
 * Modulo operation with error handling
 * Sets error_flag if divisor is zero
 */
double modulo_op(double num1, double num2, int *error_flag) {
    if (num2 == 0) {
        *error_flag = 1;
        return 0;
    }
    *error_flag = 0;
    return fmod(num1, num2);
}

/**
 * Raises num1 to the power of num2
 */
double power(double num1, double num2) {
    return pow(num1, num2);
}

/* ============================================================================
 * SCIENTIFIC FUNCTIONS
 * ============================================================================ */

/**
 * Calculates square root with error handling
 * Sets error_flag if negative number is passed
 */
double square_root(double num, int *error_flag) {
    if (num < 0) {
        *error_flag = 1;
        return 0;
    }
    *error_flag = 0;
    return sqrt(num);
}

/**
 * Returns absolute value of a number
 */
double absolute(double num) {
    return fabs(num);
}

/**
 * Calculates sine of an angle
 * use_degrees: 1 for degrees, 0 for radians
 */
double sine(double num, int use_degrees) {
    if (use_degrees) {
        num = num * M_PI / 180.0;
    }
    return sin(num);
}

/**
 * Calculates cosine of an angle
 * use_degrees: 1 for degrees, 0 for radians
 */
double cosine(double num, int use_degrees) {
    if (use_degrees) {
        num = num * M_PI / 180.0;
    }
    return cos(num);
}

/**
 * Calculates tangent of an angle
 * use_degrees: 1 for degrees, 0 for radians
 */
double tangent(double num, int use_degrees) {
    if (use_degrees) {
        num = num * M_PI / 180.0;
    }
    return tan(num);
}

/**
 * Calculates natural logarithm with error handling
 * Sets error_flag if number is <= 0
 */
double natural_log(double num, int *error_flag) {
    if (num <= 0) {
        *error_flag = 1;
        return 0;
    }
    *error_flag = 0;
    return log(num);
}

/**
 * Calculates base-10 logarithm with error handling
 * Sets error_flag if number is <= 0
 */
double log_base_10(double num, int *error_flag) {
    if (num <= 0) {
        *error_flag = 1;
        return 0;
    }
    *error_flag = 0;
    return log10(num);
}

/**
 * Calculates e raised to the power of num
 */
double exponential(double num) {
    return exp(num);
}

/**
 * Calculates factorial of a number
 * Sets error_flag if number is negative or not an integer
 */
double factorial(double num, int *error_flag) {
    if (num < 0 || num != (int)num) {
        *error_flag = 1;
        return 0;
    }
    
    *error_flag = 0;
    double result = 1;
    for (int i = 2; i <= (int)num; i++) {
        result *= i;
    }
    return result;
}

/* ============================================================================
 * DISPLAY FUNCTIONS
 * ============================================================================ */

/**
 * Displays the main menu of operations
 */
void display_menu(void) {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║      SCIENTIFIC CALCULATOR v2.0        ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    printf("Basic Operations:\n");
    printf("  +     Add\n");
    printf("  -     Subtract\n");
    printf("  *     Multiply\n");
    printf("  /     Divide\n");
    printf("  %%     Modulo\n");
    printf("  ^     Power\n\n");
    printf("Scientific Functions (Single Operand):\n");
    printf("  s     Sine (degrees)\n");
    printf("  c     Cosine (degrees)\n");
    printf("  t     Tangent (degrees)\n");
    printf("  q     Square Root\n");
    printf("  a     Absolute Value\n");
    printf("  l     Natural Logarithm\n");
    printf("  g     Log Base 10\n");
    printf("  e     e^x (Exponential)\n");
    printf("  f     Factorial\n\n");
    printf("Other:\n");
    printf("  h     Help\n");
    printf("  q     Quit\n\n");
}

/**
 * Displays help information
 */
void display_help(void) {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║           HELP & INFORMATION           ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    printf("HOW TO USE:\n");
    printf("1. Select an operation from the menu\n");
    printf("2. For binary operations (+, -, *, /, %%, ^): enter two operands\n");
    printf("3. For unary operations (s, c, t, q, a, l, g, e, f): enter one operand\n");
    printf("4. Results are displayed with up to 6 decimal places\n");
    printf("5. Trigonometric functions use degrees by default\n\n");
    printf("FEATURES:\n");
    printf("- Full error handling for invalid inputs\n");
    printf("- Input validation and buffer clearing\n");
    printf("- Continuous calculation mode\n");
    printf("- Scientific notation support\n");
    printf("- Support for both degrees and radians\n\n");
}

/* ============================================================================
 * MAIN PROGRAM
 * ============================================================================ */

/**
 * Clear input buffer to prevent issues with multiple reads
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Validate and read a double from input
 * Returns 1 if successful, 0 if failed
 */
int read_double(const char *prompt, double *num) {
    printf("%s", prompt);
    if (scanf("%lf", num) != 1) {
        clear_input_buffer();
        printf("Error: Invalid input. Please enter a valid number.\n");
        return 0;
    }
    clear_input_buffer();
    return 1;
}

/**
 * Main calculator program
 */
int main() {
    char operator;
    double num1, num2, result;
    int error_flag = 0;
    int continue_calc = 1;
    double precision = 6;  // Default precision

    display_menu();

    while (continue_calc) {
        printf("\nEnter an operation (or 'h' for help, 'q' to quit): ");
        if (scanf("%c", &operator) != 1) {
            clear_input_buffer();
            printf("Error: Invalid input.\n");
            continue;
        }
        clear_input_buffer();

        operator = tolower(operator);

        // Handle quit and help
        if (operator == 'q') {
            printf("\nThank you for using Scientific Calculator!\n");
            break;
        }

        if (operator == 'h') {
            display_help();
            continue;
        }

        // Binary operations
        if (operator == '+' || operator == '-' || operator == '*' || 
            operator == '/' || operator == '%' || operator == '^') {
            
            if (!read_double("Enter first operand: ", &num1)) continue;
            if (!read_double("Enter second operand: ", &num2)) continue;

            switch (operator) {
                case '+':
                    result = add(num1, num2);
                    printf("%.6g + %.6g = %.6g\n", num1, num2, result);
                    break;

                case '-':
                    result = subtract(num1, num2);
                    printf("%.6g - %.6g = %.6g\n", num1, num2, result);
                    break;

                case '*':
                    result = multiply(num1, num2);
                    printf("%.6g * %.6g = %.6g\n", num1, num2, result);
                    break;

                case '/':
                    result = divide(num1, num2, &error_flag);
                    if (error_flag) {
                        printf("Error: Division by zero is undefined.\n");
                    } else {
                        printf("%.6g / %.6g = %.6g\n", num1, num2, result);
                    }
                    break;

                case '%':
                    result = modulo_op(num1, num2, &error_flag);
                    if (error_flag) {
                        printf("Error: Modulo by zero is undefined.\n");
                    } else {
                        printf("%.6g %% %.6g = %.6g\n", num1, num2, result);
                    }
                    break;

                case '^':
                    result = power(num1, num2);
                    printf("%.6g ^ %.6g = %.6g\n", num1, num2, result);
                    break;
            }
        }
        // Unary operations
        else if (operator == 's' || operator == 'c' || operator == 't' || 
                 operator == 'q' || operator == 'a' || operator == 'l' || 
                 operator == 'g' || operator == 'e' || operator == 'f') {
            
            if (!read_double("Enter operand: ", &num1)) continue;

            switch (operator) {
                case 's':
                    result = sine(num1, 1);  // 1 for degrees
                    printf("sin(%.6g°) = %.6g\n", num1, result);
                    break;

                case 'c':
                    result = cosine(num1, 1);  // 1 for degrees
                    printf("cos(%.6g°) = %.6g\n", num1, result);
                    break;

                case 't':
                    result = tangent(num1, 1);  // 1 for degrees
                    printf("tan(%.6g°) = %.6g\n", num1, result);
                    break;

                case 'q':
                    result = square_root(num1, &error_flag);
                    if (error_flag) {
                        printf("Error: Cannot calculate square root of negative number.\n");
                    } else {
                        printf("√%.6g = %.6g\n", num1, result);
                    }
                    break;

                case 'a':
                    result = absolute(num1);
                    printf("|%.6g| = %.6g\n", num1, result);
                    break;

                case 'l':
                    result = natural_log(num1, &error_flag);
                    if (error_flag) {
                        printf("Error: Logarithm undefined for non-positive numbers.\n");
                    } else {
                        printf("ln(%.6g) = %.6g\n", num1, result);
                    }
                    break;

                case 'g':
                    result = log_base_10(num1, &error_flag);
                    if (error_flag) {
                        printf("Error: Logarithm undefined for non-positive numbers.\n");
                    } else {
                        printf("log10(%.6g) = %.6g\n", num1, result);
                    }
                    break;

                case 'e':
                    result = exponential(num1);
                    printf("e^%.6g = %.6g\n", num1, result);
                    break;

                case 'f':
                    result = factorial(num1, &error_flag);
                    if (error_flag) {
                        printf("Error: Factorial is only defined for non-negative integers.\n");
                    } else {
                        printf("%.0f! = %.0f\n", num1, result);
                    }
                    break;
            }
        }
        else {
            printf("Error: Invalid operator '%c'. Please try again.\n", operator);
        }
    }

    return 0;
}