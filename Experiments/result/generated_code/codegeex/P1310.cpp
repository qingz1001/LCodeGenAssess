#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100001
#define MOD 10007

// 定义运算符的优先级
int priority(char op) {
    if (op == '*') return 1;
    if (op == '+') return 0;
    return -1;
}

// 计算函数
int calculate(int a, int b, char op) {
    if (op == '*') return (a * b) % MOD;
    if (op == '+') return (a + b) % MOD;
    return -1;
}

int main() {
    int L;
    char expression[MAX_LEN];
    int stack[MAX_LEN][2]; // 用于存储运算符栈
    int top = -1;

    // 输入表达式长度和表达式
    scanf("%d", &L);
    scanf("%s", expression);

    // 遍历表达式
    for (int i = 0; i < L; i++) {
        if (expression[i] == '(') {
            // 左括号直接入栈
            stack[++top][0] = 0;
            stack[top][1] = 0;
        } else if (expression[i] == ')') {
            // 遇到右括号，计算括号内的表达式
            int count_0 = 0, count_1 = 0;
            while (stack[top][0] != 0) {
                count_0 = (count_0 + stack[top][0]) % MOD;
                count_1 = (count_1 + stack[top][1]) % MOD;
                top--;
            }
            top--;
            stack[++top][0] = count_0;
            stack[top][1] = count_1;
        } else if (expression[i] == '*' || expression[i] == '+') {
            // 遇到运算符，与栈顶运算符比较优先级
            while (top >= 0 && priority(expression[i]) <= priority(expression[stack[top][2]])) {
                int count_0 = stack[top][0];
                int count_1 = stack[top][1];
                char op = stack[top][2];
                top--;
                stack[top][0] = calculate(stack[top][0], count_0, op);
                stack[top][1] = calculate(stack[top][1], count_1, op);
            }
            // 当前运算符入栈
            stack[++top][0] = 0;
            stack[top][1] = 0;
            stack[top][2] = expression[i];
        }
    }

    // 计算最终结果
    int count_0 = 0, count_1 = 0;
    while (top >= 0) {
        count_0 = (count_0 + stack[top][0]) % MOD;
        count_1 = (count_1 + stack[top][1]) % MOD;
        top--;
    }

    // 输出结果
    printf("%d\n", count_0);
    return 0;
}