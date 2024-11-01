#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char equation[1000001];
    fgets(equation, sizeof(equation), stdin);

    int len = strlen(equation);
    if (equation[len - 1] == '\n') {
        equation[len - 1] = '\0';
        len--;
    }

    int x = -1, y = -1, z = -1;
    char op;
    int pos = 0;

    // 解析第一个数
    if (equation[0] == '?') {
        x = -2;
        pos++;
    } else {
        x = 0;
        while (pos < len && isdigit(equation[pos])) {
            x = x * 10 + (equation[pos] - '0');
            pos++;
        }
    }

    // 跳过空格
    while (pos < len && isspace(equation[pos])) pos++;

    // 获取操作符
    op = equation[pos++];

    // 跳过空格
    while (pos < len && isspace(equation[pos])) pos++;

    // 解析第二个数
    if (equation[pos] == '?') {
        y = -2;
        pos++;
    } else {
        y = 0;
        while (pos < len && isdigit(equation[pos])) {
            y = y * 10 + (equation[pos] - '0');
            pos++;
        }
    }

    // 跳过等号和空格
    while (pos < len && (equation[pos] == '=' || isspace(equation[pos]))) pos++;

    // 解析第三个数
    if (equation[pos] == '?') {
        z = -2;
    } else {
        z = 0;
        while (pos < len && isdigit(equation[pos])) {
            z = z * 10 + (equation[pos] - '0');
            pos++;
        }
    }

    // 计算结果
    int result;
    if (x == -2) {
        result = (op == '+') ? z - y : z + y;
    } else if (y == -2) {
        result = (op == '+') ? z - x : x - z;
    } else {
        result = (op == '+') ? x + y : x - y;
    }

    printf("%d\n", result);

    return 0;
}