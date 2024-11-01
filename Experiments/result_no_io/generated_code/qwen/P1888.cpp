#include <stdio.h>
#include <stdlib.h>

// 函数声明
int gcd(int a, int b);
void simplifyFraction(int *numerator, int *denominator);

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    // 确保 a 是最小的边
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if (a > c) {
        int temp = a;
        a = c;
        c = temp;
    }

    // 计算较小锐角的正弦值
    int numerator = a;
    int denominator = c;

    // 约分分数
    simplifyFraction(&numerator, &denominator);

    printf("%d/%d\n", numerator, denominator);

    return 0;
}

// 最大公约数函数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 约分分数函数
void simplifyFraction(int *numerator, int *denominator) {
    int divisor = gcd(*numerator, *denominator);
    *numerator /= divisor;
    *denominator /= divisor;
}