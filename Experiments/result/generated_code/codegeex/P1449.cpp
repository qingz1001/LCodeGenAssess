#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char s[51];
    scanf("%s", s);
    int n = strlen(s);

    int stack[51];
    int top = -1;

    for (int i = 0; i < n; i++) {
        if (s[i] == '.') {
            int num = 0;
            while (s[i] != '.') {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            stack[++top] = num;
        } else if (s[i] == '@') {
            break;
        } else {
            int a = stack[top--];
            int b = stack[top--];
            if (s[i] == '+') {
                stack[++top] = b + a;
            } else if (s[i] == '-') {
                stack[++top] = b - a;
            } else if (s[i] == '*') {
                stack[++top] = b * a;
            } else if (s[i] == '/') {
                stack[++top] = b / a;
            }
        }
    }

    printf("%d\n", stack[top]);
    return 0;
}