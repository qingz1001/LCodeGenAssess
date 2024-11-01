#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    int top;
    int data[MAX_SIZE];
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, int value) {
    if (!isFull(s)) {
        s->data[++(s->top)] = value;
    }
}

int pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return -1;
}

int peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    return -1;
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    Stack opStack;
    initStack(&opStack);
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        if (infix[i] >= '0' && infix[i] <= '9') {
            postfix[j++] = infix[i];
            postfix[j++] = ' ';
        } else if (infix[i] == '(') {
            push(&opStack, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&opStack) && peek(&opStack) != '(') {
                postfix[j++] = pop(&opStack);
                postfix[j++] = ' ';
            }
            pop(&opStack); // Pop '('
        } else {
            while (!isEmpty(&opStack) && precedence(peek(&opStack)) >= precedence(infix[i])) {
                postfix[j++] = pop(&opStack);
                postfix[j++] = ' ';
            }
            push(&opStack, infix[i]);
        }
    }

    while (!isEmpty(&opStack)) {
        postfix[j++] = pop(&opStack);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return (int)pow(a, b);
        default: return 0;
    }
}

void evaluatePostfix(char *postfix) {
    Stack valStack;
    initStack(&valStack);
    int i, a, b;

    for (i = 0; postfix[i] != '\0'; i++) {
        if (postfix[i] >= '0' && postfix[i] <= '9') {
            push(&valStack, postfix[i] - '0');
        } else if (postfix[i] != ' ') {
            b = pop(&valStack);
            a = pop(&valStack);
            push(&valStack, calculate(a, b, postfix[i]));
        }
    }

    printf("%d\n", pop(&valStack));
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("%s\n", postfix);

    evaluatePostfix(postfix);

    return 0;
}