#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, a[MAXN], b[MAXN], cnt[MAXN], sum[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        cnt[a[i] + b[i]]++;
    }

    int j = 0;
    for (int i = 0; i <= n; i++) {
        while (cnt[i] && j <= n) {
            sum[j] = i;
            j++;
            cnt[i]--;
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > sum[i] || b[i] > n - sum[i] - a[i]) {
            ans++;
        }
    }

    printf("%d\n", ans);
    return 0;
}