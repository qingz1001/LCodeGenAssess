#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 35005
#define INF 0x3f3f3f3f

int n;
int a[MAXN], b[MAXN], dp[MAXN], f[MAXN];

int min(int x, int y) {
    return x < y ? x : y;
}

int max(int x, int y) {
    return x > y ? x : y;
}

int lis() {
    memset(dp, INF, sizeof(dp));
    int len = 0;
    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(dp + 1, dp + len + 1, b[i]) - dp;
        dp[pos] = b[i];
        len = max(len, pos);
        f[i] = pos;
    }
    return len;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i] - i;
    }

    int len = lis();
    printf("%d\n", n - len);

    memset(dp, INF, sizeof(dp));
    dp[0] = -INF;
    int ans = INF;
    for (int i = 1; i <= n; i++) {
        if (f[i] == len) {
            ans = min(ans, dp[len] - a[i]);
        }
        int pos = upper_bound(dp, dp + len + 1, a[i]) - dp;
        dp[pos] = min(dp[pos], a[i]);
    }

    printf("%d\n", ans);
    return 0;
}