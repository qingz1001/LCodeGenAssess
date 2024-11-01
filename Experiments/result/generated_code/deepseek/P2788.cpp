#include <stdio.h>
#include <string.h>

int main() {
    char expression[60001];
    scanf("%s", expression);

    int result = 0;
    int number = 0;
    int sign = 1; // 1 for positive, -1 for negative

    for (int i = 0; i < strlen(expression); i++) {
        if (expression[i] >= '0' && expression[i] <= '9') {
            number = number * 10 + (expression[i] - '0');
        } else {
            result += sign * number;
            number = 0;
            if (expression[i] == '+') {
                sign = 1;
            } else if (expression[i] == '-') {
                sign = -1;
            }
        }
    }

    // Add the last number
    result += sign * number;

    printf("%d\n", result);

    return 0;
}