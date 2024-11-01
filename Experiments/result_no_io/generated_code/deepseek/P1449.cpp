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
    return -1; // Error
}

int main() {
    char s[MAX_SIZE];
    scanf("%s", s);

    Stack stack;
    initStack(&stack);

    int i = 0;
    while (s[i] != '@') {
        if (s[i] == '.') {
            i++;
            continue;
        }

        if (s[i] >= '0' && s[i] <= '9') {
            int num = 0;
            while (s[i] != '.') {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            push(&stack, num);
        } else {
            int b = pop(&stack);
            int a = pop(&stack);
            int result;
            switch (s[i]) {
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
        }
        i++;
    }

    printf("%d\n", pop(&stack));

    return 0;
}