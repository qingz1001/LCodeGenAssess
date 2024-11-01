#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    // 找到最大的偶数 m 使得 2^m < n
    // 由于 n 是正整数，因此 2^m < n 的 m 最大值是 log2(n) - 1
    // 因为 m 必须是偶数，所以需要找到最大的偶数 m
    int m = (int)(log2(n - 1) / 2) * 2;

    printf("%d\n", m);
    return 0;
}