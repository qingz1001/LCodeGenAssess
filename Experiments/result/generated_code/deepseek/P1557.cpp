#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
            i++; // Move past '('
            while (expression[i] >= '0' && expression[i] <= '9') {
                multiplier = multiplier * 10 + (expression[i] - '0');
                i++;
            }
            i++; // Move past ')'
            int number = 0;
            while (expression[i] >= '0' && expression[i] <= '9') {
                number = number * 10 + (expression[i] - '0');
                i++;
            }
            result += sign * multiplier * number;
        } else if (expression[i] >= '0' && expression[i] <= '9') {
            int number = 0;
            while (expression[i] >= '0' && expression[i] <= '9') {
                number = number * 10 + (expression[i] - '0');
                i++;
            }
            result += sign * number;
        } else {
            i++; // Skip any unexpected characters
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