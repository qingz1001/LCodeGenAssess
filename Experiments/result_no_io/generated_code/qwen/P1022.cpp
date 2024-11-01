#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char equation[100];
    scanf("%s", equation);

    int a = 0, b = 0, c = 0;
    int sign = 1;
    int coeff = 0;

    for (int i = 0; i < strlen(equation); i++) {
        if (equation[i] == '+') {
            sign = 1;
        } else if (equation[i] == '-') {
            sign = -1;
        } else if (equation[i] == '=') {
            b += sign * coeff;
            coeff = 0;
            sign = 1;
        } else if (equation[i] >= 'a' && equation[i] <= 'z') {
            a += sign * coeff;
            coeff = 0;
        } else {
            coeff = coeff * 10 + (equation[i] - '0');
        }
    }

    b += sign * coeff;
    double x = -b / (double)a;
    printf("%.3f\n", x);

    return 0;
}