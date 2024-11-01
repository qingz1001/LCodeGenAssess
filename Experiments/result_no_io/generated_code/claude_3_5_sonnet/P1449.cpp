#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

int stack[MAX_SIZE];
int top = -1;

void push(int value) {
    stack[++top] = value;
}

int pop() {
    return stack[top--];
}

int evaluate(char *expr) {
    int num = 0;
    int i = 0;
    
    while (expr[i] != '@') {
        if (expr[i] >= '0' && expr[i] <= '9') {
            num = num * 10 + (expr[i] - '0');
        } else if (expr[i] == '.') {
            push(num);
            num = 0;
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            int b = pop();
            int a = pop();
            switch(expr[i]) {
                case '+': push(a + b); break;
                case '-': push(a - b); break;
                case '*': push(a * b); break;
                case '/': push(a / b); break;
            }
        }
        i++;
    }
    return pop();
}

int main() {
    char expr[MAX_SIZE + 1];
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = 0;  // 移除换行符
    
    int result = evaluate(expr);
    printf("%d\n", result);
    
    return 0;
}