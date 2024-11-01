#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 6
#define MAX_LEN 1000

typedef struct {
    char expression[MAX_LEN];
} Expression;

void generate_expression(int n, int *values, Expression *expr) {
    if (n == 0) {
        expr->expression[0] = '\0';
        return;
    }

    int mid = 1 << (n - 1);
    for (int i = 0; i < mid; i++) {
        values[n - 1] = i % 2;
        generate_expression(n - 1, values, expr);

        if (i % 2 == 0) {
            strcat(expr->expression, "(");
        }
        char op = '!';
        if ((i & 1) == 0) {
            op = '&';
        } else {
            op = '|';
        }
        strncat(expr->expression, expr->expression + strlen(expr->expression) - 1, 1);
        strncat(expr->expression, &op, 1);
        strncat(expr->expression, expr->expression + strlen(expr->expression) - 1, 1);
        strcat(expr->expression, ")");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int *values = (int *)malloc(n * sizeof(int));
    char truth_table[(1 << n) * (n + 1)];
    getchar();
    fgets(truth_table, sizeof(truth_table), stdin);

    // Parse the truth table
    int index = 0;
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            values[j] = truth_table[index++] - '0';
        }
        int result = truth_table[index++] - '0';
        printf("%d ", result);
    }

    // Generate the expression
    Expression expr;
    generate_expression(n, values, &expr);
    printf("%s\n", expr.expression);

    free(values);
    return 0;
}