#include <stdio.h>
#include <math.h>

double add(double num1, double num2) {
    return num1 + num2;
}

double subtract(double num1, double num2) {
    return num1 - num2;
}

double multiply(double num1, double num2) {
    return num1 * num2;
}

double divide(double num1, double num2) {
    if(num2 == 0) {
        return 0;
    }
    else {
        return num1 / num2;
    }
}

double power(double num1, double num2) {
    return pow(num1, num2);
}

int main() {
    char operator;
    double num1, num2, result;

    printf("Enter an operator (+, -, *, /, ^): ");
    scanf("%c", &operator);

    printf("Enter first operand: ");
    scanf("%lf", &num1);

    printf("Enter second operand: ");
    scanf("%lf", &num2);

    switch(operator) {
        case '+':
            result = add(num1, num2);
            printf("%.2lf + %.2lf = %.2lf", num1, num2, result);
            break;
            

        case '-':
            result = subtract(num1, num2);
            printf("%.2lf - %.2lf = %.2lf", num1, num2, result);
            break;

        case '*':
            result = multiply(num1, num2);
            printf("%.2lf * %.2lf = %.2lf", num1, num2, result);
            break;

        case '/':
            result = divide(num1, num2);
            if (result!=0){
            	printf("%.2lf / %.2lf = %.2lf", num1, num2, result);
            	break;
            }
            printf("Error: division by zero");
            break;

        case '^':
            result = power(num1, num2);
            printf("%.2lf ^ %.2lf = %.2lf", num1, num2, result);
            break;

        default:
            printf("Error: Invalid operator");
    }

    return 0;
}
