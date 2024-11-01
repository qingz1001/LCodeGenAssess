#include <stdio.h>

int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        default: return 0; // 不会执行到这里
    }
}

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    char operators[] = {'+', '-', '*'};
    int numOperators = sizeof(operators) / sizeof(operators[0]);

    for (int i = 0; i < numOperators; i++) {
        for (int j = 0; j < numOperators; j++) {
            int result1 = calculate(a, b, operators[i]);
            int result2 = calculate(result1, c, operators[j]);
            if (result2 == d) {
                printf("Yes\n");
                return 0;
            }
        }
    }

    printf("No\n");
    return 0;
}