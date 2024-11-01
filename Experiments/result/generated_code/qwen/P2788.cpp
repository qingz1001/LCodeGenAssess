#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char expression[60001];
    int result = 0;
    int num = 0;
    int sign = 1;

    fgets(expression, sizeof(expression), stdin);
    for (int i = 0; i < strlen(expression); i++) {
        if (expression[i] >= '0' && expression[i] <= '9') {
            num = num * 10 + (expression[i] - '0');
        } else if (expression[i] == '+') {
            result += sign * num;
            num = 0;
            sign = 1;
        } else if (expression[i] == '-') {
            result += sign * num;
            num = 0;
            sign = -1;
        }
    }
    result += sign * num;

    printf("%d\n", result);

    return 0;
}