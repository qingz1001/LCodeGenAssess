#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void parseEquation(char *equation, int *coeff, int *constant) {
    int len = strlen(equation);
    int sign = 1;
    int current_coeff = 0;
    int current_constant = 0;
    int i = 0;

    while (i < len) {
        if (equation[i] == '=') {
            sign = -1;
            i++;
            continue;
        }

        int num = 0;
        int is_negative = 1;
        if (equation[i] == '+' || equation[i] == '-') {
            is_negative = (equation[i] == '-') ? -1 : 1;
            i++;
        }

        while (i < len && isdigit(equation[i])) {
            num = num * 10 + (equation[i] - '0');
            i++;
        }

        if (i < len && isalpha(equation[i])) {
            char variable = equation[i];
            if (num == 0) num = 1;
            current_coeff += sign * is_negative * num;
            i++;
        } else {
            current_constant += sign * is_negative * num;
        }
    }

    *coeff = current_coeff;
    *constant = current_constant;
}

int main() {
    char equation[100];
    fgets(equation, sizeof(equation), stdin);

    int coeff = 0, constant = 0;
    parseEquation(equation, &coeff, &constant);

    double result = -(double)constant / coeff;
    printf("a=%.3f\n", result);

    return 0;
}