#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char data[MAX_LEN];
    int top;
} Stack;

void initStack(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack, int size) {
    return stack->top == size - 1;
}

void push(Stack *stack, char item) {
    if (!isFull(stack, MAX_LEN)) {
        stack->data[++stack->top] = item;
    }
}

char pop(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top--];
    }
    return '\0';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    Stack operators;
    initStack(&operators);
    int i, j = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
            postfix[j++] = infix[i];
            postfix[j++] = ' ';
        } else if (infix[i] == '(') {
            push(&operators, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&operators) && operators.data[operators.top] != '(') {
                postfix[j++] = pop(&operators);
                postfix[j++] = ' ';
            }
            pop(&operators); // Remove '('
        } else {
            while (!isEmpty(&operators) && precedence(operators.data[operators.top]) >= precedence(infix[i])) {
                postfix[j++] = pop(&operators);
                postfix[j++] = ' ';
            }
            push(&operators, infix[i]);
        }
    }
    while (!isEmpty(&operators)) {
        postfix[j++] = pop(&operators);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

int main() {
    char infix[MAX_LEN], postfix[MAX_LEN];
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0'; // Remove newline character
    infixToPostfix(infix, postfix);
    printf("%s\n", postfix);
    return 0;
}