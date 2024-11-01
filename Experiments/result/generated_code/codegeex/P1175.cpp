#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int is_empty(Stack *s) {
    return s->top == -1;
}

int is_full(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, char c) {
    if (is_full(s)) {
        printf("Stack overflow\n");
        exit(1);
    }
    s->data[++s->top] = c;
}

char pop(Stack *s) {
    if (is_empty(s)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->data[s->top--];
}

char peek(Stack *s) {
    if (is_empty(s)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return s->data[s->top];
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        case '(':
        case ')':
            return 0;
        default:
            return -1;
    }
}

void infix_to_postfix(const char *infix) {
    Stack op_stack;
    init(&op_stack);
    int len = strlen(infix);
    char postfix[MAX_SIZE];
    int post_index = 0;

    for (int i = 0; i < len; i++) {
        char c = infix[i];
        if (c >= '0' && c <= '9') {
            postfix[post_index++] = c;
        } else if (c == '(') {
            push(&op_stack, c);
        } else if (c == ')') {
            while (!is_empty(&op_stack) && peek(&op_stack) != '(') {
                postfix[post_index++] = pop(&op_stack);
            }
            if (!is_empty(&op_stack) && peek(&op_stack) == '(') {
                pop(&op_stack);
            }
        } else {
            while (!is_empty(&op_stack) && precedence(peek(&op_stack)) >= precedence(c)) {
                postfix[post_index++] = pop(&op_stack);
            }
            push(&op_stack, c);
        }
    }

    while (!is_empty(&op_stack)) {
        postfix[post_index++] = pop(&op_stack);
    }

    postfix[post_index] = '\0';
    printf("%s\n", postfix);
}

int main() {
    char infix[MAX_SIZE];
    fgets(infix, MAX_SIZE, stdin);
    infix_to_postfix(infix);
    return 0;
}