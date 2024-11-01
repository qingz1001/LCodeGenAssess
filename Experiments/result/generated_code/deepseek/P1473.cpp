#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 9

char operators[MAX_N];
int n;

void evaluate(char *expression) {
    int result = 0;
    int current_number = 0;
    char last_operator = '+';

    for (int i = 0; i < strlen(expression); i++) {
        if (expression[i] >= '0' && expression[i] <= '9') {
            current_number = current_number * 10 + (expression[i] - '0');
        } else {
            if (last_operator == '+') {
                result += current_number;
            } else if (last_operator == '-') {
                result -= current_number;
            }
            current_number = 0;
            last_operator = expression[i];
        }
    }

    if (last_operator == '+') {
        result += current_number;
    } else if (last_operator == '-') {
        result -= current_number;
    }

    if (result == 0) {
        printf("%s\n", expression);
    }
}

void generate_expressions(int pos, char *expression) {
    if (pos == n) {
        evaluate(expression);
        return;
    }

    // Add ' ' (space)
    expression[2 * pos - 1] = ' ';
    generate_expressions(pos + 1, expression);

    // Add '+'
    expression[2 * pos - 1] = '+';
    generate_expressions(pos + 1, expression);

    // Add '-'
    expression[2 * pos - 1] = '-';
    generate_expressions(pos + 1, expression);
}

int main() {
    scanf("%d", &n);

    char expression[2 * MAX_N];
    for (int i = 0; i < n; i++) {
        expression[2 * i] = '1' + i;
    }
    expression[2 * n - 1] = '\0';

    generate_expressions(1, expression);

    return 0;
}