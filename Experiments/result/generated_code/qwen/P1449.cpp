#include <stdio.h>
#include <stdlib.h>

int main() {
    char s[55];
    scanf("%s", s);

    int stack[50], top = -1;
    for (int i = 0; s[i] != '@'; i++) {
        if (s[i] == '.' || s[i] >= '0' && s[i] <= '9') {
            int num = 0, negative = 0;
            if (s[i] == '-') {
                negative = 1;
                i++;
            }
            while (s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            if (negative) num = -num;
            stack[++top] = num;
            i--;
        } else {
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