#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    int min_anger = n; // 初始化最小愤怒值为 n

    // 计算最小愤怒值
    for (int i = 1; i <= m; i++) {
        int k = min(i - 1, n) + min(m - i, n);
        min_anger = min(min_anger, k);
    }

    printf("%d\n", min_anger);
    return 0;
}