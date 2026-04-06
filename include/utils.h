/**
 * @file utils.h
 * @brief Utility functions header
 * @author Sujaan Bhattacharyya
 * @version 1.0.0
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/**
 * @brief Get the history file path
 * @return Path to history file
 */
const char *get_history_path(void);

/**
 * @brief Save calculation to history
 * @param operation Operation string
 * @param result Result value
 * @return true if successful, false otherwise
 */
bool save_to_history(const char *operation, double result);

/**
 * @brief Load and display calculation history
 * @param max_items Maximum number of items to display
 */
void display_history(int max_items);

/**
 * @brief Clear calculation history
 * @return true if successful, false otherwise
 */
bool clear_history(void);

/**
 * @brief Check if a string is empty or whitespace only
 * @param str String to check
 * @return true if empty or whitespace, false otherwise
 */
bool is_empty_string(const char *str);

/**
 * @brief Trim whitespace from string
 * @param str String to trim (modified in place)
 */
void trim_string(char *str);

/**
 * @brief Get current timestamp as string
 * @param buffer Buffer to store timestamp
 * @param buffer_size Size of buffer
 */
void get_timestamp(char *buffer, int buffer_size);

/**
 * @brief Format number for display
 * @param value Number to format
 * @param precision Decimal places
 * @param buffer Buffer to store formatted string
 * @param buffer_size Size of buffer
 */
void format_number(double value, int precision, char *buffer, int buffer_size);

#endif /* UTILS_H */
