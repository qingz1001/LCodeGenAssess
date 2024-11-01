#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 递归函数计算排列数
long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// 计算给定字符串的排列数，并输出后8位
void calculate_permutations(char* str) {
    int n = strlen(str);
    long long result = factorial(n);
    printf("%lld\n", result % 100000000);
}

int main() {
    char str[1001]; // 用于存储大数
    scanf("%s", str);
    calculate_permutations(str);
    return 0;
}