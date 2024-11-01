#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SIZE 100

char infix[MAX_SIZE];
char postfix[MAX_SIZE];
char stack[MAX_SIZE];
int top = -1;

int precedence(char op) {
    switch(op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
    }
    return 0;
}

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

void infix_to_postfix() {
    int i, j = 0;
    char c;

    for (i = 0; infix[i]; i++) {
        if (isdigit(infix[i])) {
            postfix[j++] = infix[i];
            postfix[j++] = ' ';
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (top > -1 && stack[top] != '(')
                postfix[j++] = pop(), postfix[j++] = ' ';
            if (top > -1 && stack[top] == '(')
                pop();
        } else {
            while (top > -1 && precedence(stack[top]) >= precedence(infix[i]))
                postfix[j++] = pop(), postfix[j++] = ' ';
            push(infix[i]);
        }
    }

    while (top > -1)
        postfix[j++] = pop(), postfix[j++] = ' ';
    postfix[j] = '\0';
}

int calculate(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': {
            int result = 1;
            for (int i = 0; i < b; i++)
                result *= a;
            return result;
        }
    }
    return 0;
}

void evaluate_postfix() {
    int stack[MAX_SIZE], top = -1;
    char *token = strtok(postfix, " ");

    while (token != NULL) {
        if (isdigit(token[0]))
            stack[++top] = atoi(token);
        else {
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = calculate(a, b, token[0]);
        }
        printf("%s ", token);
        token = strtok(NULL, " ");
        if (token != NULL && !isdigit(token[0]))
            printf("\n");
    }
    printf("\n%d\n", stack[top]);
}

int main() {
    fgets(infix, MAX_SIZE, stdin);
    infix[strcspn(infix, "\n")] = 0;
    infix_to_postfix();
    evaluate_postfix();
    return 0;
}