#include "calculator.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    Calculator* calc = calculator_new();
    if (!calc) {
        fprintf(stderr, "Error: Could not initialize calculator\n");
        return 1;
    }
    
    int choice = 0;
    bool running = true;
    
    while (running) {
        ui_show_main_menu();
        
        printf("Enter your choice (1-7): ");
        if (scanf("%d", &choice) != 1) {
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }
        // Clear input buffer
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                ui_run_interactive(calc);
                break;
            
            case 2:
                ui_clear_screen();
                printf("Scientific Functions Guide\n");
                ui_show_categories_menu();
                printf("Select a category: ");
                int cat;
                if (scanf("%d", &cat) == 1) {
                    printf("\nCategory %d selected\n", cat);
                    printf("(For now, use the interactive calculator)\n");
                    printf("\nPress Enter to continue...");
                    getchar();
                }
                while (getchar() != '\n');
                break;
            
            case 3:
                printf("History feature available in interactive mode.\n");
                printf("Press Enter to continue...");
                getchar();
                break;
            
            case 4:
                printf("History clear feature available in interactive mode.\n");
                printf("Press Enter to continue...");
                getchar();
                break;
            
            case 5:
                ui_clear_screen();
                printf("Settings\n");
                printf("1. Set Precision (current: %d)\n", calc->precision);
                printf("2. Back\n");
                printf("Enter choice: ");
                int setting;
                if (scanf("%d", &setting) == 1) {
                    if (setting == 1) {
                        printf("Enter precision (1-15): ");
                        int precision;
                        if (scanf("%d", &precision) == 1) {
                            calculator_set_precision(calc, precision);
                            printf("Precision set to %d\n", precision);
                        }
                    }
                }
                while (getchar() != '\n');
                printf("Press Enter to continue...");
                getchar();
                break;
            
            case 6:
                ui_show_help();
                break;
            
            case 7:
                running = false;
                break;
            
            default:
                printf("Invalid choice. Please try again.\n");
                printf("Press Enter to continue...");
                getchar();
        }
    }
    
    calculator_free(calc);
    return 0;
}
