#include <stdio.h>
#include <string.h>

int main() {
    char expression[60001];
    scanf("%s", expression);

    int result = 0;
    int number = 0;
    char operation = '+';
    int length = strlen(expression);

    for (int i = 0; i < length; i++) {
        if (expression[i] >= '0' && expression[i] <= '9') {
            number = number * 10 + (expression[i] - '0');
        }
        if ((expression[i] == '+' || expression[i] == '-' || i == length - 1)) {
            if (operation == '+') {
                result += number;
            } else if (operation == '-') {
                result -= number;
            }
            operation = expression[i];
            number = 0;
        }
    }

    printf("%d\n", result);
    return 0;
}