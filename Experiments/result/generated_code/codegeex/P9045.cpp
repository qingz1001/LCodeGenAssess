#include <stdio.h>
#include <string.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // 检查是否有解
    int count[n + 1];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < k; i++) {
        count[a[i]]++;
        if (count[a[i]] > 1) {
            printf("-1\n");
            return 0;
        }
    }

    int res = 0;
    int last = -1;
    for (int i = 0; i < k; i++) {
        if (a[i] != last) {
            res++;
            last = a[i];
        }
    }

    printf("%d\n", n - k + res - 1);
    return 0;
}