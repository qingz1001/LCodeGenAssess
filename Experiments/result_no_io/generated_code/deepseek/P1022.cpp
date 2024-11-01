#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void solveEquation(char *equation) {
    int coefficient = 0, constant = 0;
    char *token = strtok(equation, "+-=");
    char *end;
    int sign = 1;
    int left_side = 1;

    while (token) {
        int value = strtol(token, &end, 10);
        if (*end == '\0') {
            constant += sign * left_side * value;
        } else if (*end == 'x') {
            if (token == end) {
                value = 1;
            } else if (end - token == 1 && *(end - 1) == '-') {
                value = -1;
            }
            coefficient += sign * left_side * value;
        }

        if (strchr(token, '=')) {
            left_side = -1;
            sign = 1;
        } else if (strchr(token, '-')) {
            sign = -1;
        } else if (strchr(token, '+')) {
            sign = 1;
        }

        token = strtok(NULL, "+-=");
    }

    if (coefficient == 0) {
        printf("No solution\n");
    } else {
        printf("%.3f\n", (double)-constant / coefficient);
    }
}

int main() {
    char equation[100];
    scanf("%s", equation);
    solveEquation(equation);
    return 0;
}