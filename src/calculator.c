#include "calculator.h"
#include "parser.h"
#include "history.h"
#include <stdlib.h>
#include <string.h>

Calculator* calculator_new(void) {
    Calculator* calc = (Calculator*)malloc(sizeof(Calculator));
    if (calc) {
        calc->last_result = 0.0;
        calc->precision = 6;
        calc->show_history = false;
        calc->history_count = 0;
    }
    return calc;
}

void calculator_free(Calculator* calc) {
    if (calc) {
        free(calc);
    }
}

bool calculator_evaluate(Calculator* calc, const char* expression, double* result) {
    if (!calc || !expression || !result) {
        return false;
    }
    
    if (!parser_evaluate(expression, result)) {
        return false;
    }
    
    calc->last_result = *result;
    return true;
}

void calculator_set_precision(Calculator* calc, int precision) {
    if (calc && precision > 0 && precision <= 15) {
        calc->precision = precision;
    }
}

double calculator_get_last_result(Calculator* calc) {
    if (calc) {
        return calc->last_result;
    }
    return 0.0;
}
