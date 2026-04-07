#include "history.h"
#include <stdlib.h>
#include <string.h>

History* history_new(void) {
    History* hist = (History*)malloc(sizeof(History));
    if (hist) {
        hist->count = 0;
        hist->current_index = -1;
    }
    return hist;
}

void history_free(History* hist) {
    if (hist) {
        free(hist);
    }
}

void history_add(History* hist, const char* expression, double result) {
    if (!hist || hist->count >= MAX_HISTORY_ENTRIES) {
        return;
    }
    
    strncpy(hist->entries[hist->count].expression, expression, MAX_EXPRESSION_LEN - 1);
    hist->entries[hist->count].expression[MAX_EXPRESSION_LEN - 1] = '\0';
    hist->entries[hist->count].result = result;
    hist->entries[hist->count].timestamp = time(NULL);
    
    hist->count++;
    hist->current_index = hist->count - 1;
}

HistoryEntry* history_prev(History* hist) {
    if (!hist || hist->count == 0) {
        return NULL;
    }
    
    if (hist->current_index > 0) {
        hist->current_index--;
    }
    
    return &hist->entries[hist->current_index];
}

HistoryEntry* history_next(History* hist) {
    if (!hist || hist->count == 0) {
        return NULL;
    }
    
    if (hist->current_index < hist->count - 1) {
        hist->current_index++;
    }
    
    return &hist->entries[hist->current_index];
}

void history_display(History* hist) {
    if (!hist || hist->count == 0) {
        printf("History is empty.\n");
        return;
    }
    
    printf("\n=== Calculation History ===\n");
    for (int i = 0; i < hist->count; i++) {
        printf("%2d. %s = %.6f\n", i + 1, hist->entries[i].expression, hist->entries[i].result);
    }
    printf("==========================\n\n");
}

void history_clear(History* hist) {
    if (hist) {
        hist->count = 0;
        hist->current_index = -1;
    }
}

HistoryEntry* history_get(History* hist, int index) {
    if (!hist || index < 0 || index >= hist->count) {
        return NULL;
    }
    return &hist->entries[index];
}
