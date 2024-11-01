#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    int top;
    char data[MAX_SIZE];
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

void push(Stack *s, char item) {
    if (!isFull(s)) {
        s->data[++(s->top)] = item;
    }
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return '\0';
}

char peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    return '\0';
}

int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*': case '/': return 2;
        case '+': case '-': return 1;
        default: return 0;
    }
}

void infixToPostfix(char *infix, char *postfix) {
    Stack opStack;
    initStack(&opStack);
    int i, j;
    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
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

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("%s\n", postfix);
    return 0;
}