#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LEN 255

int main() {
    char equation[MAX_LEN];
    fgets(equation, MAX_LEN, stdin);
    
    int len = strlen(equation);
    if (equation[len-1] == '\n') {
        equation[len-1] = '\0';
        len--;
    }

    int coeff = 0, constant = 0;
    char variable;
    int sign = 1, isLeft = 1;

    for (int i = 0; i < len; i++) {
        if (isalpha(equation[i])) {
            variable = equation[i];
            if (i > 0 && isdigit(equation[i-1])) {
                coeff += sign * isLeft * atoi(&equation[i-1]);
            } else {
                coeff += sign * isLeft;
            }
        } else if (isdigit(equation[i])) {
            int num = 0;
            while (i < len && isdigit(equation[i])) {
                num = num * 10 + (equation[i] - '0');
                i++;
            }
            i--;
            if (i+1 < len && isalpha(equation[i+1])) {
                continue;
            }
            constant += sign * isLeft * num;
        } else if (equation[i] == '+') {
            sign = 1;
        } else if (equation[i] == '-') {
            sign = -1;
        } else if (equation[i] == '=') {
            isLeft = -1;
            sign = 1;
        }
    }

    double result = (double)-constant / coeff;
    printf("%.3f\n", fabs(result) < 1e-10 ? 0 : result);

    return 0;
}