#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 200

int main() {
    int k, w;
    scanf("%d%d", &k, &w);

    // 如果w小于k，则不可能有满足条件的2^k进制数
    if (w < k) {
        printf("0\n");
        return 0;
    }

    // 计算w除以k的商和余数
    int n = w / k;
    int r = w % k;

    // 初始化结果数组，用于存储结果
    unsigned long long result[MAX_DIGITS + 1] = {0};
    result[0] = 1;

    // 遍历每一位，计算满足条件的2^k进制数的个数
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < (1 << k); ++j) {
            for (int l = k - 1; l >= 0; --l) {
                if (j & (1 << l)) {
                    result[i + 1] += result[i];
                }
            }
        }
    }

    // 处理余数部分
    for (int j = 1; j < (1 << r); ++j) {
        for (int l = r - 1; l >= 0; --l) {
            if (j & (1 << l)) {
                result[n + 1] += result[n];
            }
        }
    }

    // 输出结果
    int i = MAX_DIGITS;
    while (result[i] == 0 && i > 0) --i;
    if (i == 0) {
        printf("0\n");
    } else {
        for (; i >= 0; --i) {
            printf("%llu", result[i]);
        }
        printf("\n");
    }

    return 0;
}