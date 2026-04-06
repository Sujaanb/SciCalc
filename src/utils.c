/**
 * @file utils.c
 * @brief Utility functions implementation
 * @author Sujaan Bhattacharyya
 * @version 1.0.0
 */

#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>

#define HISTORY_DIR ".scicalc"
#define HISTORY_FILE "history.txt"
#define MAX_HISTORY_LINES 100

/**
 * @brief Get the history file path
 */
const char *get_history_path(void) {
    static char path[512];
    const char *home = getenv("HOME");
    
    if (!home) {
        home = getenv("USERPROFILE"); /* Windows */
    }
    
    if (home) {
        snprintf(path, sizeof(path), "%s/%s/%s", home, HISTORY_DIR, HISTORY_FILE);
    } else {
        snprintf(path, sizeof(path), "%s", HISTORY_FILE);
    }
    
    return path;
}

/**
 * @brief Ensure history directory exists
 */
static bool ensure_history_dir(void) {
    const char *home = getenv("HOME");
    if (!home) {
        home = getenv("USERPROFILE");
    }
    
    if (!home) return true; /* Silently fail if no home directory */
    
    char dir_path[512];
    snprintf(dir_path, sizeof(dir_path), "%s/%s", home, HISTORY_DIR);
    
    struct stat st = {0};
    if (stat(dir_path, &st) == -1) {
        /* Directory doesn't exist, try to create it */
        #ifdef _WIN32
            mkdir(dir_path);
        #else
            mkdir(dir_path, 0700);
        #endif
    }
    
    return true;
}

/**
 * @brief Save calculation to history
 */
bool save_to_history(const char *operation, double result) {
    ensure_history_dir();
    
    const char *history_path = get_history_path();
    FILE *file = fopen(history_path, "a");
    
    if (!file) {
        return false;
    }
    
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    fprintf(file, "[%s] %s = %.10g\n", timestamp, operation, result);
    fclose(file);
    
    return true;
}

/**
 * @brief Display calculation history
 */
void display_history(int max_items) {
    ensure_history_dir();
    
    const char *history_path = get_history_path();
    FILE *file = fopen(history_path, "r");
    
    if (!file) {
        printf("No history found.\n");
        return;
    }
    
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║              CALCULATION HISTORY (Last %d entries)              ║\n", max_items);
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    
    char line[512];
    int line_count = 0;
    int total_lines = 0;
    
    /* First pass: count lines */
    while (fgets(line, sizeof(line), file) && total_lines < MAX_HISTORY_LINES) {
        total_lines++;
    }
    
    /* Second pass: display last N items */
    rewind(file);
    int start_line = (total_lines > max_items) ? (total_lines - max_items) : 0;
    int current_line = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if (current_line >= start_line) {
            /* Remove newline */
            line[strcspn(line, "\n")] = 0;
            printf("║ %s\n", line);
        }
        current_line++;
    }
    
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    fclose(file);
}

/**
 * @brief Clear calculation history
 */
bool clear_history(void) {
    ensure_history_dir();
    
    const char *history_path = get_history_path();
    FILE *file = fopen(history_path, "w");
    
    if (!file) {
        return false;
    }
    
    fclose(file);
    printf("✓ History cleared.\n");
    return true;
}

/**
 * @brief Check if string is empty or whitespace only
 */
bool is_empty_string(const char *str) {
    if (!str) return true;
    
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return false;
        }
        str++;
    }
    
    return true;
}

/**
 * @brief Trim whitespace from string
 */
void trim_string(char *str) {
    if (!str) return;
    
    /* Trim leading whitespace */
    int start = 0;
    while (str[start] && isspace((unsigned char)str[start])) {
        start++;
    }
    
    /* Trim trailing whitespace */
    int end = strlen(str) - 1;
    while (end >= start && isspace((unsigned char)str[end])) {
        end--;
    }
    
    /* Shift and null terminate */
    if (start > 0) {
        memmove(str, str + start, end - start + 2);
    }
    str[end - start + 1] = '\0';
}

/**
 * @brief Get current timestamp as string
 */
void get_timestamp(char *buffer, int buffer_size) {
    if (!buffer || buffer_size <= 0) return;
    
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", timeinfo);
}

/**
 * @brief Format number for display
 */
void format_number(double value, int precision, char *buffer, int buffer_size) {
    if (!buffer || buffer_size <= 0) return;
    
    if (precision < 0) precision = 6;
    if (precision > 15) precision = 15;
    
    /* Use %g for intelligent formatting */
    snprintf(buffer, buffer_size, "%.*g", precision, value);
}