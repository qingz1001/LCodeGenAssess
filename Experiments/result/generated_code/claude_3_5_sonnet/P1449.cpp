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

int main() {
    char s[MAX_SIZE + 1];
    scanf("%s", s);

    int len = strlen(s);
    int num = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            num = num * 10 + (s[i] - '0');
        } else if (s[i] == '.') {
            push(num);
            num = 0;
        } else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            int b = pop();
            int a = pop();
            switch (s[i]) {
                case '+':
                    push(a + b);
                    break;
                case '-':
                    push(a - b);
                    break;
                case '*':
                    push(a * b);
                    break;
                case '/':
                    push(a / b);
                    break;
            }
        } else if (s[i] == '@') {
            printf("%d\n", stack[top]);
            break;
        }
    }

    return 0;
}