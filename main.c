#include "calculator.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NEWLINE_SIZE 2

/**
 * Reads and clears input buffer to prevent scanf issues
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Safely reads a double from user input
 * @return The double value read, or 0 on error
 */
double read_double(void) {
    double value;
    if (scanf("%lf", &value) != 1) {
        clear_input_buffer();
        return 0;
    }
    clear_input_buffer();
    return value;
}

/**
 * Safely reads a string from user input
 * @param buffer Buffer to store input
 * @param size Size of buffer
 */
void read_string(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        /* Remove trailing newline */
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

/**
 * Handles basic arithmetic operations
 */
void handle_basic_operation(char operator, HistoryEntry *history, int *history_count) {
    double num1, num2, result;
    int error = SUCCESS;
    char operation_str[BUFFER_SIZE];
    
    printf("Enter first operand: ");
    num1 = read_double();
    
    printf("Enter second operand: ");
    num2 = read_double();
    
    switch(operator) {
        case '+':
            result = add(num1, num2);
            snprintf(operation_str, BUFFER_SIZE, "%.2f + %.2f", num1, num2);
            printf("Result: %.2f + %.2f = %.2f\n", num1, num2, result);
            break;
            
        case '-':
            result = subtract(num1, num2);
            snprintf(operation_str, BUFFER_SIZE, "%.2f - %.2f", num1, num2);
            printf("Result: %.2f - %.2f = %.2f\n", num1, num2, result);
            break;
            
        case '*':
            result = multiply(num1, num2);
            snprintf(operation_str, BUFFER_SIZE, "%.2f * %.2f", num1, num2);
            printf("Result: %.2f * %.2f = %.2f\n", num1, num2, result);
            break;
            
        case '/':
            result = divide(num1, num2, &error);
            if (error == ERROR_DIV_ZERO) {
                print_error_message(error);
                return;
            }
            snprintf(operation_str, BUFFER_SIZE, "%.2f / %.2f", num1, num2);
            printf("Result: %.2f / %.2f = %.2f\n", num1, num2, result);
            break;
            
        case '^':
            result = power(num1, num2);
            snprintf(operation_str, BUFFER_SIZE, "%.2f ^ %.2f", num1, num2);
            printf("Result: %.2f ^ %.2f = %.2f\n", num1, num2, result);
            break;
            
        default:
            print_error_message(ERROR_INVALID_OP);
            return;
    }
    
    add_to_history(history, history_count, operation_str, result);
}

/**
 * Handles scientific operations
 */
void handle_scientific_operation(HistoryEntry *history, int *history_count) {
    char operation[20];
    double num, result;
    int int_num, error = SUCCESS;
    char operation_str[BUFFER_SIZE];
    
    print_scientific_menu();
    printf("Enter operation: ");
    read_string(operation, sizeof(operation));
    
    /* Convert to lowercase for easier comparison */
    for (int i = 0; operation[i]; i++) {
        operation[i] = tolower(operation[i]);
    }
    
    if (strcmp(operation, "back") == 0) {
        return;
    }
    
    if (strcmp(operation, "sqrt") == 0) {
        printf("Enter number: ");
        num = read_double();
        result = square_root(num, &error);
        if (error == ERROR_INVALID_INPUT) {
            print_error_message(error);
            return;
        }
        snprintf(operation_str, BUFFER_SIZE, "sqrt(%.2f)", num);
        printf("Result: sqrt(%.2f) = %.2f\n", num, result);
        
    } else if (strcmp(operation, "sin") == 0) {
        printf("Enter angle in radians: ");
        num = read_double();
        result = sine(num);
        snprintf(operation_str, BUFFER_SIZE, "sin(%.2f)", num);
        printf("Result: sin(%.2f) = %.2f\n", num, result);
        
    } else if (strcmp(operation, "cos") == 0) {
        printf("Enter angle in radians: ");
        num = read_double();
        result = cosine(num);
        snprintf(operation_str, BUFFER_SIZE, "cos(%.2f)", num);
        printf("Result: cos(%.2f) = %.2f\n", num, result);
        
    } else if (strcmp(operation, "tan") == 0) {
        printf("Enter angle in radians: ");
        num = read_double();
        result = tangent(num);
        snprintf(operation_str, BUFFER_SIZE, "tan(%.2f)", num);
        printf("Result: tan(%.2f) = %.2f\n", num, result);
        
    } else if (strcmp(operation, "log") == 0) {
        printf("Enter number: ");
        num = read_double();
        result = logarithm(num, &error);
        if (error == ERROR_INVALID_INPUT) {
            print_error_message(error);
            return;
        }
        snprintf(operation_str, BUFFER_SIZE, "log(%.2f)", num);
        printf("Result: log(%.2f) = %.2f\n", num, result);
        
    } else if (strcmp(operation, "fact") == 0) {
        printf("Enter integer (0-20): ");
        if (scanf("%d", &int_num) != 1) {
            clear_input_buffer();
            print_error_message(ERROR_INVALID_INPUT);
            return;
        }
        clear_input_buffer();
        
        result = factorial(int_num, &error);
        if (error == ERROR_INVALID_INPUT) {
            print_error_message(error);
            return;
        }
        snprintf(operation_str, BUFFER_SIZE, "%d!", int_num);
        printf("Result: %d! = %.0f\n", int_num, result);
        
    } else {
        print_error_message(ERROR_INVALID_OP);
        return;
    }
    
    add_to_history(history, history_count, operation_str, result);
}

/**
 * Main function - calculator loop
 */
int main(void) {
    char input[20];
    HistoryEntry history[MAX_HISTORY];
    int history_count = 0;
    int running = 1;
    
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║     Welcome to SciCalc v2.0            ║\n");
    printf("║   A Scientific Calculator in C         ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    while (running) {
        print_menu();
        printf("Enter operation: ");
        read_string(input, sizeof(input));
        
        if (strlen(input) == 0) {
            continue;
        }
        
        /* Convert to lowercase */
        char op = tolower(input[0]);
        
        switch(op) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                handle_basic_operation(op, history, &history_count);
                break;
                
            case 's':
                handle_scientific_operation(history, &history_count);
                break;
                
            case 'h':
                print_history(history, history_count);
                break;
                
            case 'q':
                printf("Thank you for using SciCalc! Goodbye!\n\n");
                running = 0;
                break;
                
            default:
                print_error_message(ERROR_INVALID_OP);
        }
    }
    
    return 0;
}
