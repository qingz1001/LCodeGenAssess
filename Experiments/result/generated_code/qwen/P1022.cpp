#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char equation[100];
    scanf("%s", equation);

    int coeff_a = 0, const_term = 0;
    int sign = 1;
    int i = 0;

    while (equation[i] != '=') {
        if (equation[i] == '+') {
            sign = 1;
        } else if (equation[i] == '-') {
            sign = -1;
        } else if (equation[i] >= '0' && equation[i] <= '9') {
            int num = 0;
            while (i < strlen(equation) && equation[i] >= '0' && equation[i] <= '9') {
                num = num * 10 + (equation[i] - '0');
                i++;
            }
            if (i < strlen(equation) && equation[i] == 'a') {
                coeff_a += sign * num;
            } else {
                const_term += sign * num;
            }
            i--;
        }
        i++;
    }

    i++;

    while (i < strlen(equation)) {
        if (equation[i] == '+') {
            sign = 1;
        } else if (equation[i] == '-') {
            sign = -1;
        } else if (equation[i] >= '0' && equation[i] <= '9') {
            int num = 0;
            while (i < strlen(equation) && equation[i] >= '0' && equation[i] <= '9') {
                num = num * 10 + (equation[i] - '0');
                i++;
            }
            if (i < strlen(equation) && equation[i] == 'a') {
                coeff_a -= sign * num;
            } else {
                const_term -= sign * num;
            }
            i--;
        }
        i++;
    }

    double solution = (double)const_term / coeff_a;
    printf("a=%.3f\n", solution);

    return 0;
}