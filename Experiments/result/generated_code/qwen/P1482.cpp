#include <stdio.h>
#include <stdlib.h>

// 函数声明
int gcd(int a, int b);
void reduceFraction(int *numerator, int *denominator);

int main() {
    int num1, den1, num2, den2;
    scanf("%d/%d", &num1, &den1);
    scanf("%d/%d", &num2, &den2);

    // 约分两个分数
    reduceFraction(&num1, &den1);
    reduceFraction(&num2, &den2);

    // 计算乘积
    int productNum = num1 * num2;
    int productDen = den1 * den2;

    // 约分乘积后的分数
    reduceFraction(&productNum, &productDen);

    // 找到乘积在 Cantor 表中的位置
    int row = productDen;
    int col = productNum + productDen - 1;

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
void reduceFraction(int *numerator, int *denominator) {
    int divisor = gcd(*numerator, *denominator);
    *numerator /= divisor;
    *denominator /= divisor;
}