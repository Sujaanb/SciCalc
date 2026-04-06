/**
 * @file main.c
 * @brief Main entry point for SciCalc - Production Ready Scientific Calculator
 * @author Sujaan Bhattacharyya
 * @version 1.0.0
 * 
 * SciCalc is a comprehensive scientific calculator with:
 * - 25+ mathematical operations
 * - Comprehensive error handling
 * - Input validation
 * - Calculation history
 * - Interactive menu system
 */

#include "include/calculator.h"
#include "include/parser.h"
#include "include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 256
#define MAX_HISTORY_DISPLAY 10

/* Function prototypes */
void display_main_menu(void);
void display_help(void);
void perform_binary_operation(OperationType op);
void perform_unary_operation(OperationType op);
CalculationResult execute_operation(OperationType op, double op1, double op2);

/**
 * @brief Main entry point
 */
int main(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║              SciCalc - Scientific Calculator v1.0              ║\n");
    printf("║                   Production Ready Edition                    ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
    
    char input[INPUT_BUFFER_SIZE];
    int running = 1;
    
    while (running) {
        display_main_menu();
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input. Exiting...\n");
            break;
        }
        
        /* Remove trailing newline */
        input[strcspn(input, "\n")] = 0;
        trim_string(input);
        
        if (is_empty_string(input)) {
            continue;
        }
        
        char choice = tolower(input[0]);
        
        switch (choice) {
            case 'a':
                perform_binary_operation(OP_ADD);
                break;
            case 's':
                if (strlen(input) > 1 && input[1] == 'q') {
                    perform_unary_operation(OP_SQRT);
                } else if (strcmp(input, "sin") == 0) {
                    perform_unary_operation(OP_SIN);
                } else {
                    perform_binary_operation(OP_SUBTRACT);
                }
                break;
            case 'm':
                perform_binary_operation(OP_MULTIPLY);
                break;
            case 'd':
                perform_binary_operation(OP_DIVIDE);
                break;
            case 'p':
                perform_binary_operation(OP_POWER);
                break;
            case 'q':
                if (strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) {
                    running = 0;
                }
                break;
            case 'h':
                if (strcmp(input, "help") == 0 || strcmp(input, "h") == 0) {
                    display_help();
                } else if (strcmp(input, "history") == 0) {
                    display_history(MAX_HISTORY_DISPLAY);
                }
                break;
            default:
                printf("❌ Unknown command. Type 'help' for available operations.\n\n");
                break;
        }
    }
    
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║                 Thank you for using SciCalc!                  ║\n");
    printf("║                    Goodbye! See you soon.                     ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
    
    return EXIT_SUCCESS;
}

/**
 * @brief Display main menu
 */
void display_main_menu(void) {
    printf("\n┌───────────────────────────────────────────────────────────────┐\n");
    printf("│ Select Operation:                                              │\n");
    printf("│ (a)dd  (s)ubtract  (m)ultiply  (d)ivide  (p)ower               │\n");
    printf("│ sqrt  sin  cos  tan  exp  log  (h)elp  (q)uit                 │\n");
    printf("└───────────────────────────────────────────────────────────────┘\n");
    printf("> ");
}

/**
 * @brief Display help information
 */
void display_help(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║                    AVAILABLE OPERATIONS                         ║\n");
    printf("╠═══════════════════════════════════════════════════════════════╣\n");
    printf("║ BASIC OPERATIONS (Binary - 2 operands):                        ║\n");
    printf("║  • add, +       - Addition                                     ║\n");
    printf("║  • subtract, - - Subtraction                                 ║\n");
    printf("║  • multiply, * - Multiplication                              ║\n");
    printf("║  • divide, /   - Division                                     ║\n");
    printf("║  • power, ^    - Power (a raised to b)                        ║\n");
    printf("║  • mod, %%      - Modulo (remainder)                          ║\n");
    printf("║                                                                 ║\n");
    printf("║ ALGEBRAIC FUNCTIONS (Unary - 1 operand):                       ║\n");
    printf("║  • sqrt        - Square Root                                  ║\n");
    printf("║  • cbrt        - Cube Root                                     ║\n");
    printf("║  • abs         - Absolute Value                                ║\n");
    printf("║  • ceil        - Ceiling (round up)                           ║\n");
    printf("║  • floor       - Floor (round down)                           ║\n");
    printf("║  • round       - Round to nearest integer                      ║\n");
    printf("║  • fact        - Factorial (max 170)                          ║\n");
    printf("║                                                                 ║\n");
    printf("║ TRIGONOMETRIC FUNCTIONS (in radians):                          ║\n");
    printf("║  • sin, cos, tan           - Sine, Cosine, Tangent            ║\n");
    printf("║  • asin, acos, atan        - Arc functions                    ║\n");
    printf("║  • sinh, cosh, tanh        - Hyperbolic functions             ║\n");
    printf("║                                                                 ║\n");
    printf("║ LOGARITHMIC & EXPONENTIAL:                                      ║\n");
    printf("║  • exp         - e^x (exponential)                            ║\n");
    printf("║  • ln, log     - Natural logarithm (base e)                   ║\n");
    printf("║  • log10       - Common logarithm (base 10)                   ║\n");
    printf("║  • log2        - Binary logarithm (base 2)                    ║\n");
    printf("║                                                                 ║\n");
    printf("║ UTILITY COMMANDS:                                               ║\n");
    printf("║  • history     - Show calculation history (last 10)           ║\n");
    printf("║  • help        - Show this help message                       ║\n");
    printf("║  • quit        - Exit the calculator                          ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    printf("\nNote: Trigonometric functions work with radians.\n");
    printf("      To convert: radians = degrees * 3.14159265359 / 180\n\n");
}

/**
 * @brief Perform binary operation (2 operands)
 */
void perform_binary_operation(OperationType op) {
    char input[INPUT_BUFFER_SIZE];
    double operand1, operand2;
    
    printf("\n─── %s ───\n", get_operation_name(op));
    
    /* Get first operand */
    printf("Enter first number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("❌ Error reading input.\n");
        return;
    }
    
    if (!is_valid_number(input, &operand1)) {
        printf("❌ Invalid number format.\n");
        return;
    }
    
    /* Get second operand */
    printf("Enter second number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("❌ Error reading input.\n");
        return;
    }
    
    if (!is_valid_number(input, &operand2)) {
        printf("❌ Invalid number format.\n");
        return;
    }
    
    /* Execute operation */
    CalculationResult result = execute_operation(op, operand1, operand2);
    
    /* Display result */
    char operation_str[256];
    char op_symbol[8];
    
    switch (op) {
        case OP_ADD:      strcpy(op_symbol, "+"); break;
        case OP_SUBTRACT: strcpy(op_symbol, "-"); break;
        case OP_MULTIPLY: strcpy(op_symbol, "*"); break;
        case OP_DIVIDE:   strcpy(op_symbol, "/"); break;
        case OP_POWER:    strcpy(op_symbol, "^"); break;
        case OP_MODULO:   strcpy(op_symbol, "%"); break;
        default:          strcpy(op_symbol, "?"); break;
    }
    
    snprintf(operation_str, sizeof(operation_str), "%.10g %s %.10g", operand1, op_symbol, operand2);
    print_result(result, operation_str);
    
    if (result.error == ERR_SUCCESS) {
        save_to_history(operation_str, result.value);
    }
}

/**
 * @brief Perform unary operation (1 operand)
 */
void perform_unary_operation(OperationType op) {
    char input[INPUT_BUFFER_SIZE];
    double operand;
    
    printf("\n─── %s ───\n", get_operation_name(op));
    printf("Enter number: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("❌ Error reading input.\n");
        return;
    }
    
    if (!is_valid_number(input, &operand)) {
        printf("❌ Invalid number format.\n");
        return;
    }
    
    /* Execute operation */
    CalculationResult result = execute_operation(op, operand, 0);
    
    /* Display result */
    char operation_str[256];
    const char *func_name = get_operation_name(op);
    snprintf(operation_str, sizeof(operation_str), "%s(%.10g)", func_name, operand);
    
    print_result(result, operation_str);
    
    if (result.error == ERR_SUCCESS) {
        save_to_history(operation_str, result.value);
    }
}

/**
 * @brief Execute operation based on type
 */
CalculationResult execute_operation(OperationType op, double op1, double op2) {
    switch (op) {
        /* Binary operations */
        case OP_ADD:        return calc_add(op1, op2);
        case OP_SUBTRACT:   return calc_subtract(op1, op2);
        case OP_MULTIPLY:   return calc_multiply(op1, op2);
        case OP_DIVIDE:     return calc_divide(op1, op2);
        case OP_POWER:      return calc_power(op1, op2);
        case OP_MODULO:     return calc_modulo(op1, op2);
        
        /* Unary algebraic */
        case OP_SQRT:       return calc_sqrt(op1);
        case OP_CBRT:       return calc_cbrt(op1);
        case OP_FACTORIAL:  return calc_factorial(op1);
        case OP_ABS:        return calc_abs(op1);
        case OP_CEIL:       return calc_ceil(op1);
        case OP_FLOOR:      return calc_floor(op1);
        case OP_ROUND:      return calc_round(op1);
        
        /* Trigonometric */
        case OP_SIN:        return calc_sin(op1);
        case OP_COS:        return calc_cos(op1);
        case OP_TAN:        return calc_tan(op1);
        case OP_ASIN:       return calc_asin(op1);
        case OP_ACOS:       return calc_acos(op1);
        case OP_ATAN:       return calc_atan(op1);
        
        /* Hyperbolic */
        case OP_SINH:       return calc_sinh(op1);
        case OP_COSH:       return calc_cosh(op1);
        case OP_TANH:       return calc_tanh(op1);
        
        /* Exponential & Logarithmic */
        case OP_EXP:        return calc_exp(op1);
        case OP_LOG:        return calc_log(op1);
        case OP_LOG10:      return calc_log10(op1);
        case OP_LOG2:       return calc_log2(op1);
        
        default:
            return (CalculationResult){0, ERR_INVALID_OPERATOR, "Invalid operation"};
    }
}