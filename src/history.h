#ifndef HISTORY_H
#define HISTORY_H

#include <time.h>

/**
 * @file history.h
 * @brief Calculation history management
 */

#define MAX_HISTORY_ENTRIES 100
#define MAX_EXPRESSION_LEN 256

typedef struct {
    char expression[MAX_EXPRESSION_LEN];
    double result;
    time_t timestamp;
} HistoryEntry;

typedef struct {
    HistoryEntry entries[MAX_HISTORY_ENTRIES];
    int count;
    int current_index;
} History;

/**
 * Create new history
 */
History* history_new(void);

/**
 * Free history
 */
void history_free(History* hist);

/**
 * Add entry to history
 */
void history_add(History* hist, const char* expression, double result);

/**
 * Get previous entry
 */
HistoryEntry* history_prev(History* hist);

/**
 * Get next entry
 */
HistoryEntry* history_next(History* hist);

/**
 * Display history
 */
void history_display(History* hist);

/**
 * Clear history
 */
void history_clear(History* hist);

/**
 * Get history entry by index
 */
HistoryEntry* history_get(History* hist, int index);

#endif // HISTORY_H
