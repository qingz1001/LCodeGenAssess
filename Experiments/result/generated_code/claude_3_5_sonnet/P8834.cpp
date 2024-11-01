#include <stdio.h>

#define MAX_N 1003

int main() {
    int n, k;
    int a[MAX_N];
    long long count = 0;

    // 读取输入
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // 计算和谐对的数量
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((long long)a[i] * a[j] <= k) {
                count++;
            }
        }
    }

    // 输出结果
    printf("%lld\n", count);

    return 0;
}