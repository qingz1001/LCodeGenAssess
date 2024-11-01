#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 51

typedef struct {
    int a;
    int b;
    char op;
} Stack;

int evaluate(char *exp, int a) {
    Stack stack[MAX_LEN];
    int top = -1;
    int i = 0;
    int len = strlen(exp);
    int num1, num2, result;

    while (i < len) {
        if (exp[i] == ' ') {
            i++;
            continue;
        }
        if (exp[i] == 'a') {
            stack[++top].a = a;
            stack[top].b = 0;
            i++;
        } else if (exp[i] >= '0' && exp[i] <= '9') {
            stack[++top].a = 0;
            while (i < len && exp[i] >= '0' && exp[i] <= '9') {
                stack[top].a = stack[top].a * 10 + (exp[i] - '0');
                i++;
            }
            stack[top].b = 0;
        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '^') {
            stack[++top].op = exp[i];
            i++;
        } else if (exp[i] == '(') {
            stack[++top].a = 0;
            stack[top].b = 1;
            i++;
        } else if (exp[i] == ')') {
            while (stack[top].b != 1) {
                num2 = stack[top].a;
                top--;
                num1 = stack[top].a;
                top--;
                result = stack[top].op == '+' ? num1 + num2 : 
                         stack[top].op == '-' ? num1 - num2 : 
                         stack[top].op == '*' ? num1 * num2 : 
                         num1 ^ num2;
                stack[top].a = result;
            }
            top--;
            i++;
        }
    }

    while (top > 0) {
        num2 = stack[top].a;
        top--;
        num1 = stack[top].a;
        top--;
        result = stack[top].op == '+' ? num1 + num2 : 
                 stack[top].op == '-' ? num1 - num2 : 
                 stack[top].op == '*' ? num1 * num2 : 
                 num1 ^ num2;
        stack[top].a = result;
    }

    return stack[0].a;
}

int main() {
    char mainExp[MAX_LEN];
    scanf("%[^\n]", mainExp);
    getchar(); // consume newline

    int n;
    scanf("%d", &n);
    getchar(); // consume newline

    char options[26][MAX_LEN];
    for (int i = 0; i < n; i++) {
        scanf("%[^\n]", options[i]);
        getchar(); // consume newline
    }

    int mainResult = evaluate(mainExp, 1);

    for (int i = 0; i < n; i++) {
        if (evaluate(options[i], 1) == mainResult) {
            printf("%c", 'A' + i);
        }
    }

    return 0;
}