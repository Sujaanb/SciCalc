#ifndef CALCULATOR_H
#define CALCULATOR_H

#define PRECISION 2
#define MAX_HISTORY 100
#define BUFFER_SIZE 256

/* Error codes */
#define ERROR_DIV_ZERO -1
#define ERROR_INVALID_OP -2
#define ERROR_INVALID_INPUT -3
#define SUCCESS 0

/* Structure for storing calculation history */
typedef struct {
    char operation[BUFFER_SIZE];
    double result;
} HistoryEntry;

/* Basic arithmetic operations */
double add(double num1, double num2);
double subtract(double num1, double num2);
double multiply(double num1, double num2);
double divide(double num1, double num2, int *error);
double power(double num1, double num2);

/* Scientific operations */
double square_root(double num, int *error);
double sine(double num);
double cosine(double num);
double tangent(double num);
double logarithm(double num, int *error);
double factorial(int num, int *error);

/* Utility functions */
int is_valid_operator(char op);
void print_menu(void);
void print_scientific_menu(void);
void print_error_message(int error_code);
void add_to_history(HistoryEntry *history, int *history_count, const char *operation, double result);
void print_history(HistoryEntry *history, int history_count);

#endif /* CALCULATOR_H */
