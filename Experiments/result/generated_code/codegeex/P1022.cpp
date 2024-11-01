#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char equation[1000];
    fgets(equation, sizeof(equation), stdin); // 读取一元一次方程

    int length = strlen(equation);
    int x_count = 0; // x的系数
    int constant = 0; // 常数项
    int sign = 1; // 符号，初始为正
    int num = 0; // 当前数字

    for (int i = 0; i < length; i++) {
        if (equation[i] == 'x') {
            if (num != 0) {
                x_count += sign * num;
            } else {
                x_count += sign;
            }
            num = 0;
        } else if (equation[i] == '+' || equation[i] == '-') {
            if (num != 0) {
                constant += sign * num;
            }
            num = 0;
            sign = (equation[i] == '+') ? 1 : -1;
        } else if (equation[i] == '=') {
            if (num != 0) {
                constant += sign * num;
            }
            num = 0;
            sign = 1;
        } else if (equation[i] >= '0' && equation[i] <= '9') {
            num = num * 10 + (equation[i] - '0');
        }
    }

    if (num != 0) {
        constant += sign * num;
    }

    double result = (double)constant / x_count;
    printf("%.3f\n", result);

    return 0;
}