#include <stdio.h>

// 函数声明
int gcd(int a, int b);
void simplifyFraction(int *numerator, int *denominator);

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    // 找出斜边 c
    int hypotenuse = a > b ? (a > c ? a : c) : (b > c ? b : c);
    int leg1, leg2;

    // 确定直角边
    if (hypotenuse == a) {
        leg1 = b;
        leg2 = c;
    } else if (hypotenuse == b) {
        leg1 = a;
        leg2 = c;
    } else {
        leg1 = a;
        leg2 = b;
    }

    // 计算较小锐角的正弦值
    int numerator = leg1 < leg2 ? leg1 : leg2;
    int denominator = hypotenuse;

    // 约分
    simplifyFraction(&numerator, &denominator);

    // 输出结果
    printf("%d/%d\n", numerator, denominator);

    return 0;
}

// 计算最大公约数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 约分分数
void simplifyFraction(int *numerator, int *denominator) {
    int commonDivisor = gcd(*numerator, *denominator);
    *numerator /= commonDivisor;
    *denominator /= commonDivisor;
}