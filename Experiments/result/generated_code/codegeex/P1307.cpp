#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    // 如果N是0，直接输出0
    if (N == 0) {
        printf("0\n");
        return 0;
    }

    int sign = 1; // 用于记录N的正负号
    if (N < 0) {
        sign = -1;
        N = -N; // 将N转为正数方便处理
    }

    int reversed = 0; // 用于存储反转后的数字
    while (N > 0) {
        int digit = N % 10; // 获取N的个位数
        reversed = reversed * 10 + digit; // 将个位数添加到反转后的数字中
        N /= 10; // 去掉N的个位数
    }

    printf("%d\n", sign * reversed); // 输出反转后的数字，带上原来的正负号
    return 0;
}