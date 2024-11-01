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
    if (isFull(s)) {
        printf("Stack is full.\n");
        exit(1);
    }
    s->data[++s->top] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        exit(1);
    }
    return s->data[s->top--];
}

int evaluatePostfixExpression(char *expression) {
    Stack s;
    initStack(&s);
    int i = 0;
    while (expression[i] != '@') {
        if (expression[i] == '.') {
            int num = 0;
            int sign = 1;
            if (expression[i - 1] == '-') {
                sign = -1;
            }
            for (int j = i - 2; j >= 0 && expression[j] >= '0' && expression[j] <= '9'; j--) {
                num = num * 10 + (expression[j] - '0');
                i--;
            }
            push(&s, sign * num);
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            int op2 = pop(&s);
            int op1 = pop(&s);
            int result;
            switch (expression[i]) {
                case '+':
                    result = op1 + op2;
                    break;
                case '-':
                    result = op1 - op2;
                    break;
                case '*':
                    result = op1 * op2;
                    break;
                case '/':
                    result = op1 / op2;
                    break;
            }
            push(&s, result);
        }
        i++;
    }
    return pop(&s);
}

int main() {
    char expression[MAX_SIZE];
    fgets(expression, MAX_SIZE, stdin);
    expression[strcspn(expression, "\n")] = 0; // Remove trailing newline character if present
    int result = evaluatePostfixExpression(expression);
    printf("%d\n", result);
    return 0;
}