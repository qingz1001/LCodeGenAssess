#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 2005

int main() {
    char expression[MAX_LEN];
    scanf("%s", expression);

    int result = 0;
    int sign = 1;
    int number = 0;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '+') {
            sign = 1;
        } else if (expression[i] == '-') {
            sign = -1;
        } else if (expression[i] >= '0' && expression[i] <= '9') {
            number = number * 10 + (expression[i] - '0');
        } else if (expression[i] == '(' || expression[i] == ')') {
            if (expression[i] == '(') {
                number *= sign;
                sign = 1;
            }
            result += number;
            number = 0;
        }
    }

    printf("%d\n", result);
    return 0;
}