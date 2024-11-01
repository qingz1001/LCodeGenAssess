#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 51

typedef struct {
    char op;
    int val;
} Token;

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int apply_op(int a, int b, char op) {
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
    Token stack[MAX_LEN];
    int top = -1;
    char op_stack[MAX_LEN];
    int op_top = -1;

    for (i = 0; tokens[i] != '\0'; i++) {
        if (tokens[i] == ' ') continue;

        if (tokens[i] == 'a') {
            stack[++top].op = '\0';
            stack[top].val = a;
        } else if (isdigit(tokens[i])) {
            int val = 0;
            while (isdigit(tokens[i])) {
                val = val * 10 + (tokens[i] - '0');
                i++;
            }
            i--;
            stack[++top].op = '\0';
            stack[top].val = val;
        } else if (tokens[i] == '(') {
            op_stack[++op_top] = '(';
        } else if (tokens[i] == ')') {
            while (op_top != -1 && op_stack[op_top] != '(') {
                char op = op_stack[op_top--];
                int b = stack[top--].val;
                int a = stack[top--].val;
                stack[++top].op = '\0';
                stack[top].val = apply_op(a, b, op);
            }
            op_top--;
        } else {
            while (op_top != -1 && precedence(op_stack[op_top]) >= precedence(tokens[i])) {
                char op = op_stack[op_top--];
                int b = stack[top--].val;
                int a = stack[top--].val;
                stack[++top].op = '\0';
                stack[top].val = apply_op(a, b, op);
            }
            op_stack[++op_top] = tokens[i];
        }
    }

    while (op_top != -1) {
        char op = op_stack[op_top--];
        int b = stack[top--].val;
        int a = stack[top--].val;
        stack[++top].op = '\0';
        stack[top].val = apply_op(a, b, op);
    }

    return stack[top].val;
}

int main() {
    char expr[MAX_LEN];
    int n;
    char options[26][MAX_LEN];
    int i;

    scanf(" %[^\n]", expr);
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf(" %[^\n]", options[i]);
    }

    int a_values[] = {1, 2, 3};
    int num_values = sizeof(a_values) / sizeof(a_values[0]);

    int expr_results[num_values];
    for (i = 0; i < num_values; i++) {
        expr_results[i] = evaluate(expr, a_values[i]);
    }

    char result[27] = {0};
    int result_index = 0;

    for (i = 0; i < n; i++) {
        int option_results[num_values];
        for (int j = 0; j < num_values; j++) {
            option_results[j] = evaluate(options[i], a_values[j]);
        }

        int is_equivalent = 1;
        for (int j = 0; j < num_values; j++) {
            if (option_results[j] != expr_results[j]) {
                is_equivalent = 0;
                break;
            }
        }

        if (is_equivalent) {
            result[result_index++] = 'A' + i;
        }
    }

    printf("%s\n", result);

    return 0;
}