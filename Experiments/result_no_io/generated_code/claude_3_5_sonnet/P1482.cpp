#include <stdio.h>

// 计算最大公约数
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// 简化分数
void simplify(int *num, int *den) {
    int d = gcd(*num, *den);
    *num /= d;
    *den /= d;
}

// 计算分数在Cantor表中的位置
void find_position(int num, int den, int *row, int *col) {
    if (num == 1) {
        *row = 1;
        *col = den;
    } else if (den == 1) {
        *row = num;
        *col = 1;
    } else {
        *row = num;
        *col = den;
    }
}

int main() {
    int num1, den1, num2, den2;
    
    // 读取输入
    scanf("%d/%d", &num1, &den1);
    scanf("%d/%d", &num2, &den2);
    
    // 计算乘积
    int result_num = num1 * num2;
    int result_den = den1 * den2;
    
    // 简化结果
    simplify(&result_num, &result_den);
    
    // 找到位置
    int row, col;
    find_position(result_num, result_den, &row, &col);
    
    // 输出结果
    printf("%d %d\n", col, row);
    
    return 0;
}