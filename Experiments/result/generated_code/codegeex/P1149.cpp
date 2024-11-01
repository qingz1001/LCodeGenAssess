#include <stdio.h>

int match[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}; // 火柴棒数量数组
int count = 0;

int main() {
    int n;
    scanf("%d", &n);
    n -= 4; // 减去加号和等号各两根火柴棍

    // 枚举所有可能的A和B
    for (int a = 0; a < 10000; a++) {
        for (int b = 0; b < 10000; b++) {
            int c = a + b;
            if (c >= 10000) continue; // 如果C是个四位数，跳过

            // 计算火柴棒数量
            int total = match[a / 1000] + match[a % 1000 / 100] + match[a % 100 / 10] + match[a % 10] +
                        match[b / 1000] + match[b % 1000 / 100] + match[b % 100 / 10] + match[b % 10] +
                        match[c / 1000] + match[c % 1000 / 100] + match[c % 100 / 10] + match[c % 10];

            if (total == n) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}