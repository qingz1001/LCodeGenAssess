#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LEN 51
#define MAX_OPTIONS 26
#define MAX_EVALS 10

typedef struct {
    char expr[MAX_LEN];
    int result[MAX_EVALS];
} Expression;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '^': return (int)pow(a, b);
    }
    return 0;
}

int evaluate(char* tokens, int a) {
    int i;
    int values[MAX_LEN];
    char ops[MAX_LEN];
    int values_top = -1, ops_top = -1;

    for (i = 0; i < strlen(tokens); i++) {
        if (tokens[i] == ' ') continue;

        if (isdigit(tokens[i])) {
            int val = 0;
            while (i < strlen(tokens) && isdigit(tokens[i])) {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }
            i--;
            values[++values_top] = val;
        } else if (tokens[i] == 'a') {
            values[++values_top] = a;
        } else if (tokens[i] == '(') {
            ops[++ops_top] = tokens[i];
        } else if (tokens[i] == ')') {
            while (ops_top != -1 && ops[ops_top] != '(') {
                int val2 = values[values_top--];
                int val1 = values[values_top--];
                char op = ops[ops_top--];
                values[++values_top] = applyOp(val1, val2, op);
            }
            ops_top--;
        } else {
            while (ops_top != -1 && precedence(ops[ops_top]) >= precedence(tokens[i])) {
                int val2 = values[values_top--];
                int val1 = values[values_top--];
                char op = ops[ops_top--];
                values[++values_top] = applyOp(val1, val2, op);
            }
            ops[++ops_top] = tokens[i];
        }
    }

    while (ops_top != -1) {
        int val2 = values[values_top--];
        int val1 = values[values_top--];
        char op = ops[ops_top--];
        values[++values_top] = applyOp(val1, val2, op);
    }

    return values[values_top];
}

void evaluateExpression(Expression* expr) {
    for (int a = 1; a <= MAX_EVALS; a++) {
        expr->result[a - 1] = evaluate(expr->expr, a);
    }
}

int main() {
    Expression mainExpr;
    scanf("%s", mainExpr.expr);
    evaluateExpression(&mainExpr);

    int n;
    scanf("%d", &n);
    Expression options[MAX_OPTIONS];
    for (int i = 0; i < n; i++) {
        scanf("%s", options[i].expr);
        evaluateExpression(&options[i]);
    }

    char result[MAX_OPTIONS + 1] = {0};
    int result_index = 0;

    for (int i = 0; i < n; i++) {
        int equal = 1;
        for (int a = 0; a < MAX_EVALS; a++) {
            if (mainExpr.result[a] != options[i].result[a]) {
                equal = 0;
                break;
            }
        }
        if (equal) {
            result[result_index++] = 'A' + i;
        }
    }

    printf("%s\n", result);
    return 0;
}