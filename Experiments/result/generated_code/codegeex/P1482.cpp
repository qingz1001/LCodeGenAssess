#include <stdio.h>

// 求最大公约数
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// 约分函数
void reduceFraction(int *numerator, int *denominator) {
    int divisor = gcd(*numerator, *denominator);
    *numerator /= divisor;
    *denominator /= divisor;
}

// 将分数转换为在Cantor表中的行列位置
void findPosition(int numerator, int denominator, int *row, int *column) {
    int p = 1, q = 1;
    while (numerator != 1 && denominator != 1) {
        if (numerator > denominator) {
            numerator -= denominator;
        } else if (denominator > numerator) {
            denominator -= numerator;
        }
        p++;
    }
    if (numerator == 1) {
        *row = p;
        *column = 1;
    } else {
        *row = 1;
        *column = p;
    }
}

int main() {
    int numerator1, denominator1, numerator2, denominator2;
    scanf("%d/%d", &numerator1, &denominator1);
    scanf("%d/%d", &numerator2, &denominator2);

    // 约分
    reduceFraction(&numerator1, &denominator1);
    reduceFraction(&numerator2, &denominator2);

    // 计算乘积
    int productNumerator = numerator1 * numerator2;
    int productDenominator = denominator1 * denominator2;

    // 约分乘积
    reduceFraction(&productNumerator, &productDenominator);

    // 找到乘积在Cantor表中的行列位置
    int row, column;
    findPosition(productNumerator, productDenominator, &row, &column);

    // 输出结果
    printf("%d %d\n", column, row);

    return 0;
}