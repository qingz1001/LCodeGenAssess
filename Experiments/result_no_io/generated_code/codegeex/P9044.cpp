#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int a[2001];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    int min_gifts = n - k; // 初始假设所有人都拿到礼物，再减去至少需要的礼物数量

    for (int i = 1; i <= n; i++) {
        int gifts = 0;
        for (int j = 1; j <= n; j++) {
            if (a[j] < a[i]) {
                gifts++;
            }
        }
        if (gifts < min_gifts) {
            min_gifts = gifts;
        }
    }

    printf("%d\n", min_gifts);
    return 0;
}