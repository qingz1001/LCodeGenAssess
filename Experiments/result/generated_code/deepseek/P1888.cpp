#include <stdio.h>

// 函数用于计算最大公约数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    // 找到最小的两个数
    int min1 = a < b ? a : b;
    min1 = min1 < c ? min1 : c;
    int min2 = a + b + c - min1 - (a > b ? (a > c ? a : c) : (b > c ? b : c));

    // 计算较小锐角的正弦值
    int numerator = min1;
    int denominator = (min1 == a || min1 == b) ? c : b;

    // 约分
    int common_divisor = gcd(numerator, denominator);
    numerator /= common_divisor;
    denominator /= common_divisor;

    // 输出结果
    printf("%d/%d\n", numerator, denominator);

    return 0;
}