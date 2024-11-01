#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char equation[1000000];
    fgets(equation, sizeof(equation), stdin);
    int len = strlen(equation);
    int i, x, y, z;
    char op;

    // 去除空格
    for (i = 0; i < len; i++) {
        if (equation[i] == ' ') {
            for (int j = i; j < len; j++) {
                equation[j] = equation[j + 1];
            }
            len--;
            i--;
        }
    }

    // 找出未知数的位置
    int unknown_pos = -1;
    for (i = 0; i < len; i++) {
        if (equation[i] == '?') {
            unknown_pos = i;
            break;
        }
    }

    // 解析数字
    sscanf(equation, "%d%c%d=%d", &x, &op, &y, &z);

    // 根据运算符和未知数的位置计算结果
    switch (op) {
        case '+':
            if (unknown_pos == 0) {
                printf("%d\n", z - y);
            } else if (unknown_pos == 1) {
                printf("%d\n", z - x);
            } else {
                printf("%d\n", x + y);
            }
            break;
        case '-':
            if (unknown_pos == 0) {
                printf("%d\n", x + y - z);
            } else if (unknown_pos == 1) {
                printf("%d\n", x - z);
            } else {
                printf("%d\n", x + z);
            }
            break;
    }

    return 0;
}