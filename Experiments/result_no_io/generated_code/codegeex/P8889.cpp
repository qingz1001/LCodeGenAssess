#include <stdio.h>

int main() {
    long long n, m, a[500005], b[500005];
    int cutPoints[500005] = {0}, segments = 0;
    char c;

    // 读取序列长度 n 和序列 b 的长度 m
    while ((c = getchar()) < '0' || c > '9');
    n = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') n = n * 10 + c - '0';
    while ((c = getchar()) < '0' || c > '9');
    m = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') m = m * 10 + c - '0';

    // 读取序列 a
    for (long long i = 0; i < n; i++) {
        while ((c = getchar()) < '0' || c > '9');
        a[i] = c - '0';
        while ((c = getchar()) >= '0' && c <= '9') a[i] = a[i] * 10 + c - '0';
    }

    // 读取序列 b 并标记切割点
    for (long long i = 0; i < m; i++) {
        while ((c = getchar()) < '0' || c > '9');
        b[i] = c - '0';
        while ((c = getchar()) >= '0' && c <= '9') b[i] = b[i] * 10 + c - '0';
        for (long long j = 0; j < n; j++) {
            if (a[j] == b[i]) cutPoints[j] = 1;
        }
    }

    // 计算片段数量
    for (long long i = 0; i < n; i++) {
        if (cutPoints[i] || (i == 0 && cutPoints[i] == 0)) {
            segments++;
        }
    }

    // 输出片段数量
    printf("%d\n", segments);

    return 0;
}