#include <stdio.h>
#include <string.h>

int main() {
    char equation[1000001];
    scanf("%s", equation);

    int x, y, z;
    char op;

    // Find the operator and parse the numbers
    for (int i = 0; i < strlen(equation); i++) {
        if (equation[i] == '+' || equation[i] == '-') {
            op = equation[i];
            sscanf(equation, "%d%c%d=%d", &x, &op, &y, &z);
            break;
        }
    }

    // Calculate the missing number based on the operator
    int result;
    if (op == '+') {
        result = z - y;
    } else if (op == '-') {
        result = z + y;
    }

    printf("%d\n", result);

    return 0;
}