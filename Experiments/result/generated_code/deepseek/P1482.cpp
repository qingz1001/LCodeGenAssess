#include <stdio.h>
#include <stdlib.h>

// 函数声明
int gcd(int a, int b);
void simplifyFraction(int *numerator, int *denominator);
void findPosition(int numerator, int denominator, int *row, int *col);

int main() {
    int num1, den1, num2, den2;
    int num_product, den_product;
    int row, col;

    // 读取输入
    scanf("%d/%d", &num1, &den1);
    scanf("%d/%d", &num2, &den2);

    // 计算积的分子和分母
    num_product = num1 * num2;
    den_product = den1 * den2;

    // 约分
    simplifyFraction(&num_product, &den_product);

    // 找到积在表中的位置
    findPosition(num_product, den_product, &row, &col);

    // 输出结果
    printf("%d %d\n", row, col);

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
    int common_divisor = gcd(*numerator, *denominator);
    *numerator /= common_divisor;
    *denominator /= common_divisor;
}

// 找到分数在表中的位置
void findPosition(int numerator, int denominator, int *row, int *col) {
    // 如果分子为1，则直接计算
    if (numerator == 1) {
        *row = denominator;
        *col = 1;
    } else if (denominator == 1) {
        *row = 1;
        *col = numerator;
    } else {
        // 计算行和列
        int n = numerator + denominator - 1;
        int sum = n * (n + 1) / 2;
        if (n % 2 == 0) {
            *row = numerator;
            *col = denominator;
        } else {
            *row = denominator;
            *col = numerator;
        }
    }
}