#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 检查一个数是否是波浪数
bool isWaveNumber(int num, int base) {
    char digits[32];
    int len = 0;
    while (num > 0) {
        digits[len++] = num % base;
        num /= base;
    }
    if (len == 1) return true; // 只有一位数也是波浪数
    for (int i = 1; i < len; i++) {
        if (digits[i] == digits[i - 1]) return false;
    }
    return true;
}

// 检查一个数是否是指定重数的波浪数
bool isKWaveNumber(int num, int l, int r, int k) {
    int count = 0;
    for (int base = l; base <= r; base++) {
        if (isWaveNumber(num, base)) count++;
        if (count >= k) return true;
    }
    return false;
}

int main() {
    int l, r, L, R, k;
    scanf("%d %d %d %d %d", &l, &r, &L, &R, &k);

    for (int num = L; num <= R; num++) {
        if (isKWaveNumber(num, l, r, k)) {
            printf("%d\n", num);
        }
    }

    return 0;
}