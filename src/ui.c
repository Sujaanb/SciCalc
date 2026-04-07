#include "ui.h"
#include "calculator.h"
#include "parser.h"
#include "history.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ANSI Color codes */
#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[34m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RED "\033[31m"
#define COLOR_CYAN "\033[36m"

static History* g_history = NULL;

void ui_clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ui_print_colored(const char* text, const char* color) {
    printf("%s%s%s", color, text, COLOR_RESET);
}

void ui_show_main_menu(void) {
    ui_clear_screen();
    ui_print_colored("\n╔════════════════════════════════════════╗\n", COLOR_CYAN);
    ui_print_colored("║         ", COLOR_CYAN);
    ui_print_colored("SciCalc v2.0 - Scientific Calculator", COLOR_BLUE);
    ui_print_colored("        ║\n", COLOR_CYAN);
    ui_print_colored("╚════════════════════════════════════════╝\n", COLOR_CYAN);
    
    printf("\n");
    ui_print_colored("Main Menu:", COLOR_GREEN);
    printf("\n");
    printf("  1. Calculator (Interactive Mode)\n");
    printf("  2. Scientific Functions\n");
    printf("  3. View History\n");
    printf("  4. Clear History\n");
    printf("  5. Settings\n");
    printf("  6. Help\n");
    printf("  7. Exit\n");
    printf("\n");
}

void ui_show_help(void) {
    ui_clear_screen();
    ui_print_colored("SciCalc - Help\n\n", COLOR_GREEN);
    
    printf("Supported Operations:\n");
    printf("  +   : Addition              Example: 5 + 3\n");
    printf("  -   : Subtraction           Example: 10 - 4\n");
    printf("  *   : Multiplication        Example: 6 * 7\n");
    printf("  /   : Division              Example: 20 / 4\n");
    printf("  ^   : Power                 Example: 2 ^ 8\n");
    printf("  %%   : Modulo                Example: 17 %% 5\n\n");
    
    printf("Trigonometric Functions (radians):\n");
    printf("  sin(x), cos(x), tan(x)\n");
    printf("  asin(x), acos(x), atan(x)\n");
    printf("  sin_deg(x), cos_deg(x), tan_deg(x)\n\n");
    
    printf("Logarithmic Functions:\n");
    printf("  ln(x), log(x), log2(x), log10(x)\n");
    printf("  exp(x)\n\n");
    
    printf("Other Functions:\n");
    printf("  sqrt(x), cbrt(x), abs(x), factorial(x)\n");
    printf("  floor(x), ceil(x), round(x)\n\n");
    
    printf("Constants:\n");
    printf("  pi or PI\n");
    printf("  e\n");
    printf("  phi (golden ratio)\n\n");
    
    printf("Examples:\n");
    printf("  sin(pi/2) = 1\n");
    printf("  sqrt(16) = 4\n");
    printf("  2^10 = 1024\n");
    printf("  (5 + 3) * 2 = 16\n\n");
    
    printf("Press Enter to continue...");
    getchar();
}

void ui_show_categories_menu(void) {
    printf("\n");
    ui_print_colored("Function Categories:\n", COLOR_GREEN);
    printf("  1. Basic Arithmetic\n");
    printf("  2. Trigonometric\n");
    printf("  3. Logarithmic/Exponential\n");
    printf("  4. Advanced Functions\n");
    printf("  5. Back to Main\n\n");
}

bool ui_get_input(char* buffer, int size) {
    if (!buffer || size <= 0) {
        return false;
    }
    
    if (fgets(buffer, size, stdin) != NULL) {
        // Remove newline if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        return true;
    }
    return false;
}

void ui_display_result(double result, int precision) {
    printf("\nResult: ");
    ui_print_colored("=", COLOR_GREEN);
    printf(" ");
    ui_print_colored("[", COLOR_YELLOW);
    printf("%.*f", precision, result);
    ui_print_colored("]\n", COLOR_YELLOW);
}

void ui_run_interactive(Calculator* calc) {
    if (!g_history) {
        g_history = history_new();
    }
    
    ui_clear_screen();
    ui_print_colored("\n╔════════════════════════════════════════╗\n", COLOR_CYAN);
    ui_print_colored("║         Interactive Calculator         ║\n", COLOR_CYAN);
    ui_print_colored("╚════════════════════════════════════════╝\n", COLOR_CYAN);
    
    printf("\nEnter expressions to calculate (type 'help' for syntax, 'quit' to exit):\n\n");
    
    char input[256];
    while (1) {
        ui_print_colored("calc> ", COLOR_BLUE);
        
        if (!ui_get_input(input, sizeof(input))) {
            break;
        }
        
        if (strlen(input) == 0) {
            continue;
        }
        
        if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }
        
        if (strcmp(input, "help") == 0) {
            ui_show_help();
            continue;
        }
        
        if (strcmp(input, "history") == 0) {
            history_display(g_history);
            continue;
        }
        
        if (strcmp(input, "clear") == 0) {
            history_clear(g_history);
            printf("History cleared.\n");
            continue;
        }
        
        if (strcmp(input, "last") == 0) {
            double last = calculator_get_last_result(calc);
            printf("Last result: %.*f\n", calc->precision, last);
            continue;
        }
        
        double result = 0.0;
        if (calculator_evaluate(calc, input, &result)) {
            ui_display_result(result, calc->precision);
            history_add(g_history, input, result);
        } else {
            ui_print_colored("\nError: Invalid expression\n", COLOR_RED);
        }
        printf("\n");
    }
}
