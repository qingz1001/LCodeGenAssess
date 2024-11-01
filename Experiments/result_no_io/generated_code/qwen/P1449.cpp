#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char s[60];
    scanf("%s", s);
    
    int stack[51], top = -1;
    for (int i = 0; s[i] != '@'; i++) {
        if (s[i] == '.' || s[i] >= '0' && s[i] <= '9') {
            // Push number to stack
            int num = 0;
            while (s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + (s[i++] - '0');
            }
            stack[++top] = num;
            i--; // Adjust index after reading a number
        } else {
            // Pop two numbers and perform the operation
            int b = stack[top--];
            int a = stack[top--];
            switch (s[i]) {
                case '+':
                    stack[++top] = a + b;
                    break;
                case '-':
                    stack[++top] = a - b;
                    break;
                case '*':
                    stack[++top] = a * b;
                    break;
                case '/':
                    stack[++top] = a / b;
                    break;
            }
        }
    }
    
    printf("%d\n", stack[top]);
    return 0;
}