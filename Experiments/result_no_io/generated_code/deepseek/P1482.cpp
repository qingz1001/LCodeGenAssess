#include <stdio.h>

// 求最大公约数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 约分分数
void simplify(int *numerator, int *denominator) {
    int common_divisor = gcd(*numerator, *denominator);
    *numerator /= common_divisor;
    *denominator /= common_divisor;
}

int main() {
    int num1, den1, num2, den2;
    
    // 读取第一个分数
    scanf("%d/%d", &num1, &den1);
    // 读取第二个分数
    scanf("%d/%d", &num2, &den2);
    
    // 计算积的分子和分母
    int product_num = num1 * num2;
    int product_den = den1 * den2;
    
    // 约分
    simplify(&product_num, &product_den);
    
    // 如果分母为1，则视为整数
    if (product_den == 1) {
        printf("%d %d\n", product_num, 1);
    } else {
        // 计算在Cantor表中的位置
        int n = product_num + product_den - 1;
        int sum = n * (n + 1) / 2;
        int position = sum - (product_den - 1);
        
        // 计算列和行
        int row = position;
        int col = n - position + 1;
        
        printf("%d %d\n", row, col);
    }
    
    return 0;
}