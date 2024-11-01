#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    // 确保 a <= b
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // 威佐夫博弈的特定位公式
    // 如果 a = (m * (1 + sqrt(5)) / 2) * n, 则先手必败
    // 其中 m 和 n 为非负整数
    double golden_ratio = (1 + sqrt(5)) / 2;
    double k = a / golden_ratio;

    // 计算整数部分和分数部分
    int integer_part = (int)k;
    double fractional_part = k - integer_part;

    // 如果分数部分接近于 0，则先手必败
    if (fractional_part < 1e-9) {
        printf("0\n"); // 先手必败
    } else {
        printf("1\n"); // 先手必胜
    }

    return 0;
}