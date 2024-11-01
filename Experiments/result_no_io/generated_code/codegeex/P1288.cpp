#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[21];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // 检查是否有0，如果有0则先手必胜
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) {
            printf("YES\n");
            return 0;
        }
    }

    // 检查相邻两个数的和是否为偶数，如果有则先手必胜
    for (int i = 1; i <= n; i++) {
        if ((a[i] + a[i % n + 1]) % 2 == 0) {
            printf("YES\n");
            return 0;
        }
    }

    // 其他情况先手必败
    printf("NO\n");
    return 0;
}