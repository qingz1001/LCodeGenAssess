#include <stdio.h>

int main() {
    int m, n;
    scanf("%d%d", &m, &n);

    int t[n], w[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    // 按照扣款数从大到小排序
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (w[j] < w[j + 1]) {
                int temp_t = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp_t;

                int temp_w = w[j];
                w[j] = w[j + 1];
                w[j + 1] = temp_w;
            }
        }
    }

    // 遍历所有小游戏，尽量按照扣款数从大到小完成
    for (int i = 0; i < n; i++) {
        if (t[i] > i) {
            m -= w[i];
        }
    }

    printf("%d\n", m);
    return 0;
}