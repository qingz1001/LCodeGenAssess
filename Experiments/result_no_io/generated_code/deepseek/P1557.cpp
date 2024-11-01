#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int evaluateKruscalExpression(char *expression) {
    int result = 0;
    int sign = 1; // 1 for positive, -1 for negative
    int i = 0;

    while (expression[i] != '\0') {
        if (expression[i] == '+') {
            sign = 1;
            i++;
        } else if (expression[i] == '-') {
            sign = -1;
            i++;
        } else if (expression[i] == '(') {
            int multiplier = 0;
            i++;
            while (expression[i] >= '0' && expression[i] <= '9') {
                multiplier = multiplier * 10 + (expression[i] - '0');
                i++;
            }
            i++; // skip ')'
            int number = 0;
            while (expression[i] >= '0' && expression[i] <= '9') {
                number = number * 10 + (expression[i] - '0');
                i++;
            }
            result += sign * multiplier * number;
        } else {
            int number = 0;
            while (expression[i] >= '0' && expression[i] <= '9') {
                number = number * 10 + (expression[i] - '0');
                i++;
            }
            result += sign * number;
        }
    }

    return result;
}

int main() {
    char expression[2001];
    scanf("%s", expression);
    int result = evaluateKruscalExpression(expression);
    printf("%d\n", result);
    return 0;
}