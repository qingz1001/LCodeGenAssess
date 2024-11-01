#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 定义运算符优先级
int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// 计算函数
double calculate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '^': return pow(a, b);
    }
    return 0;
}

// 检查表达式是否等价
int check_equivalence(char *expression, double a) {
    int len = strlen(expression);
    char stack[len];
    int top = -1;
    int i = 0;
    double num = 0;
    char op = '\0';
    int num_len = 0;
    int num_dot = 0;

    while (i < len) {
        if (expression[i] == ' ') {
            i++;
            continue;
        }
        if (isdigit(expression[i])) {
            num = num * 10 + (expression[i] - '0');
            num_len++;
            i++;
            if (expression[i] == '.') {
                num_dot = 1;
                i++;
                while (isdigit(expression[i])) {
                    num = num + (expression[i] - '0') / pow(10, num_len);
                    num_len++;
                    i++;
                }
                break;
            }
        } else {
            if (num_len > 0) {
                if (num_dot) {
                    stack[++top] = num;
                } else {
                    stack[++top] = num;
                }
                num = 0;
                num_len = 0;
                num_dot = 0;
            }
            if (expression[i] == '(') {
                stack[++top] = '(';
                i++;
            } else if (expression[i] == ')') {
                while (top >= 0 && stack[top] != '(') {
                    double b = stack[top--];
                    double a = stack[top--];
                    op = stack[top--];
                    stack[++top] = calculate(a, b, op);
                }
                top--;
                i++;
            } else {
                while (top >= 0 && priority(stack[top]) >= priority(expression[i])) {
                    double b = stack[top--];
                    double a = stack[top--];
                    op = stack[top--];
                    stack[++top] = calculate(a, b, op);
                }
                stack[++top] = expression[i];
                i++;
            }
        }
    }
    if (num_len > 0) {
        if (num_dot) {
            stack[++top] = num;
        } else {
            stack[++top] = num;
        }
    }
    while (top > 0) {
        double b = stack[top--];
        double a = stack[top--];
        op = stack[top--];
        stack[++top] = calculate(a, b, op);
    }
    return stack[top] == a;
}

int main() {
    char main_expression[51];
    scanf("%s", main_expression);

    int n;
    scanf("%d", &n);

    char expressions[27][51];
    for (int i = 0; i < n; i++) {
        scanf("%s", expressions[i]);
    }

    for (int i = 0; i < n; i++) {
        if (check_equivalence(expressions[i], 1)) {
            printf("%c", 'A' + i);
        }
    }
    printf("\n");

    return 0;
}