#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

void push(Stack *s, int value) {
    if (s->top < MAX_SIZE - 1) {
        s->data[++(s->top)] = value;
    }
}

int pop(Stack *s) {
    if (s->top >= 0) {
        return s->data[(s->top)--];
    }
    return -1; // Error case
}

int evaluatePostfix(char *expression) {
    Stack stack;
    initStack(&stack);
    int i = 0;

    while (expression[i] != '@') {
        if (expression[i] == '.') {
            i++;
            continue;
        }

        if (expression[i] >= '0' && expression[i] <= '9') {
            int num = 0;
            while (expression[i] >= '0' && expression[i] <= '9') {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            push(&stack, num);
        } else {
            int b = pop(&stack);
            int a = pop(&stack);
            int result;

            switch (expression[i]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
            }
            push(&stack, result);
            i++;
        }
    }

    return pop(&stack);
}

int main() {
    char expression[MAX_SIZE];
    scanf("%s", expression);
    int result = evaluatePostfix(expression);
    printf("%d\n", result);
    return 0;
}