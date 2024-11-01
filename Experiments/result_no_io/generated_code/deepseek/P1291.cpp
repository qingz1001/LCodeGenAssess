#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 最大公约数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 计算组合数
long long comb(int n, int k) {
    long long result = 1;
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

// 计算阶乘
long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// 计算期望值
void calculate_expectation(int n) {
    long long numerator = 0;
    long long denominator = factorial(n);

    for (int i = 1; i <= n; i++) {
        numerator += i * comb(n, i) * factorial(n - i);
    }

    // 化简分数
    long long common_divisor = gcd(numerator, denominator);
    numerator /= common_divisor;
    denominator /= common_divisor;

    // 计算整数部分
    long long integer_part = numerator / denominator;
    numerator %= denominator;

    // 输出结果
    if (numerator == 0) {
        printf("%lld\n", integer_part);
    } else {
        // 计算减号的数量
        int dash_count = 0;
        long long temp = denominator;
        while (temp > 0) {
            temp /= 10;
            dash_count++;
        }

        // 输出分子
        printf("%lld\n", numerator);

        // 输出整数部分和分数线
        if (integer_part > 0) {
            printf("%lld", integer_part);
        }
        for (int i = 0; i < dash_count; i++) {
            printf("-");
        }
        printf("\n");

        // 输出分母
        printf("%lld\n", denominator);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    calculate_expectation(n);
    return 0;
}