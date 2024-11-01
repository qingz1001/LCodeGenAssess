#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int a[5001], b[5001], c[5001];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a[i], &b[i], &c[i]);
    }

    int mic[30001] = {0}; // mic[i] 表示第 i 个位置是否需要话筒，1 表示需要，0 表示不需要

    for (int i = 0; i < m; i++) {
        for (int j = a[i]; j <= b[i]; j++) {
            mic[j] = 1;
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (mic[i] == 1) {
            cnt++;
        }
    }

    printf("%d\n", cnt);
    return 0;
}