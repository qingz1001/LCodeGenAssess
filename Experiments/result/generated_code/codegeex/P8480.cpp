#include <stdio.h>

int main() {
    long long n, m, a[1000005], max = 0, min = 1000000000;

    // 读取输入
    scanf("%lld %lld", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    // 遍历每个数，进行 m 次操作，并计算最大极差
    for (int i = 0; i < n; i++) {
        long long max_val = a[i];
        for (int j = 0; j < m; j++) {
            max_val = (max_val * 2 > 1000000000) ? 1000000000 : max_val * 2;
        }
        if (max_val > max) {
            max = max_val;
        }
    }

    for (int i = 0; i < n; i++) {
        long long min_val = a[i];
        for (int j = 0; j < m; j++) {
            if (min_val % 2 == 0) {
                min_val = min_val / 2;
            } else {
                min_val = min_val - 1;
            }
        }
        if (min_val < min) {
            min = min_val;
        }
    }

    // 输出最大极差
    printf("%lld\n", max - min);

    return 0;
}