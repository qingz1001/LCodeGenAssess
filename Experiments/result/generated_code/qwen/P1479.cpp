#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    // 初始化结果变量
    int result = 0;

    // 计算不同放法出现的五子连线的数量
    if (n >= 5) result += 1; // 行
    if (n >= 5) result += 1; // 列
    if (n >= 9) result += 1; // 对角线1
    if (n >= 9) result += 1; // 对角线2

    // 输出结果
    printf("%d\n", result);

    return 0;
}