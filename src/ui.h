#ifndef UI_H
#define UI_H

#include "calculator.h"

/**
 * @file ui.h
 * @brief User interface and menu system
 */

/**
 * Display main menu
 */
void ui_show_main_menu(void);

/**
 * Display help menu
 */
void ui_show_help(void);

/**
 * Display operation categories menu
 */
void ui_show_categories_menu(void);

/**
 * Run interactive calculator
 */
void ui_run_interactive(Calculator* calc);

/**
 * Display result with formatting
 */
void ui_display_result(double result, int precision);

/**
 * Get user input safely
 */
bool ui_get_input(char* buffer, int size);

/**
 * Clear screen
 */
void ui_clear_screen(void);

/**
 * Display colored text (ANSI codes)
 */
void ui_print_colored(const char* text, const char* color);

#endif // UI_H
