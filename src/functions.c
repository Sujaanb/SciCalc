#include "functions.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

/* Basic Arithmetic Operations */
double func_add(double a, double b) {
    return a + b;
}

double func_subtract(double a, double b) {
    return a - b;
}

double func_multiply(double a, double b) {
    return a * b;
}

double func_divide(double a, double b) {
    if (b == 0.0) {
        return 0.0; // Error: division by zero
    }
    return a / b;
}

double func_power(double base, double exponent) {
    return pow(base, exponent);
}

double func_modulo(double a, double b) {
    if (b == 0.0) {
        return 0.0; // Error: modulo by zero
    }
    return fmod(a, b);
}

/* Trigonometric Functions */
double func_sin(double x) {
    return sin(x);
}

double func_cos(double x) {
    return cos(x);
}

double func_tan(double x) {
    return tan(x);
}

double func_asin(double x) {
    if (x < -1.0 || x > 1.0) {
        return 0.0; // Domain error
    }
    return asin(x);
}

double func_acos(double x) {
    if (x < -1.0 || x > 1.0) {
        return 0.0; // Domain error
    }
    return acos(x);
}

double func_atan(double x) {
    return atan(x);
}

/* Logarithmic and Exponential Functions */
double func_ln(double x) {
    if (x <= 0.0) {
        return 0.0; // Domain error
    }
    return log(x);
}

double func_log10(double x) {
    if (x <= 0.0) {
        return 0.0; // Domain error
    }
    return log10(x);
}

double func_log2(double x) {
    if (x <= 0.0) {
        return 0.0; // Domain error
    }
    return log2(x);
}

double func_exp(double x) {
    return exp(x);
}

/* Other Mathematical Functions */
double func_sqrt(double x) {
    if (x < 0.0) {
        return 0.0; // Domain error
    }
    return sqrt(x);
}

double func_cbrt(double x) {
    return cbrt(x);
}

double func_abs(double x) {
    return fabs(x);
}

double func_factorial(double x) {
    return func_factorial_calc((int)x);
}

double func_floor(double x) {
    return floor(x);
}

double func_ceil(double x) {
    return ceil(x);
}

double func_round(double x) {
    return round(x);
}

/* Combinatorics */
double func_factorial_calc(int n) {
    if (n < 0) {
        return 0.0; // Error
    }
    if (n == 0 || n == 1) {
        return 1.0;
    }
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

double func_combination(int n, int k) {
    if (k > n || k < 0 || n < 0) {
        return 0.0; // Error
    }
    if (k == 0 || k == n) {
        return 1.0;
    }
    // C(n, k) = n! / (k! * (n-k)!)
    double numerator = func_factorial_calc(n);
    double denominator = func_factorial_calc(k) * func_factorial_calc(n - k);
    return numerator / denominator;
}

double func_permutation(int n, int k) {
    if (k > n || k < 0 || n < 0) {
        return 0.0; // Error
    }
    // P(n, k) = n! / (n-k)!
    return func_factorial_calc(n) / func_factorial_calc(n - k);
}

/* Statistical Functions */
double func_mean(double* values, int count) {
    if (count == 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += values[i];
    }
    return sum / count;
}

double func_median(double* values, int count) {
    if (count == 0) return 0.0;
    // Simple sort for median calculation
    double* temp = malloc(count * sizeof(double));
    memcpy(temp, values, count * sizeof(double));
    
    // Bubble sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                double t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }
    
    double median;
    if (count % 2 == 0) {
        median = (temp[count / 2 - 1] + temp[count / 2]) / 2.0;
    } else {
        median = temp[count / 2];
    }
    
    free(temp);
    return median;
}

double func_std_dev(double* values, int count) {
    if (count == 0) return 0.0;
    double mean = func_mean(values, count);
    double sum_sq = 0.0;
    for (int i = 0; i < count; i++) {
        double diff = values[i] - mean;
        sum_sq += diff * diff;
    }
    return sqrt(sum_sq / count);
}

/* Conversion Functions */
double deg_to_rad(double degrees) {
    return degrees * (PI / 180.0);
}

double rad_to_deg(double radians) {
    return radians * (180.0 / PI);
}
