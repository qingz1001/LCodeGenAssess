#include <stdio.h>
#include <string.h>

int main() {
    char expression[255];
    char stack[20];
    int top = -1;
    int i;

    // 读取表达式
    fgets(expression, sizeof(expression), stdin);
    int len = strlen(expression);

    // 遍历表达式
    for (i = 0; i < len; i++) {
        if (expression[i] == '(') {
            // 左括号入栈
            stack[++top] = '(';
        } else if (expression[i] == ')') {
            // 右括号出栈
            if (top == -1) {
                // 栈为空，右括号多于左括号
                printf("NO\n");
                return 0;
            }
            top--;
        }
    }

    // 检查栈是否为空
    if (top == -1) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}