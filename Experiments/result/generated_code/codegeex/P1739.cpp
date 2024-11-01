#include <stdio.h>
#include <string.h>

int main() {
    char expr[256];
    char stack[20];
    int top = -1;
    int i;

    // 读取输入的表达式
    fgets(expr, sizeof(expr), stdin);
    expr[strlen(expr) - 1] = '\0'; // 去掉换行符

    for (i = 0; expr[i] != '@'; i++) {
        if (expr[i] == '(') {
            stack[++top] = expr[i];
        } else if (expr[i] == ')') {
            if (top == -1) {
                printf("NO\n");
                return 0;
            }
            top--;
        }
    }

    if (top == -1) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}