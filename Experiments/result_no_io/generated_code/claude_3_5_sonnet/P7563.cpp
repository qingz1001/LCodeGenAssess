#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

int n;
int a[MAXN], h[MAXN], c[MAXN];
ll dp[MAXN];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

ll min(ll a, ll b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i], &h[i], &c[i]);
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    int idx[MAXN];
    for (int i = 1; i <= n; i++) idx[i] = i;
    qsort(idx + 1, n, sizeof(int), cmp);

    for (int i = 1; i <= n; i++) {
        int u = idx[i];
        for (int j = h[u]; j <= 1000000000; j++) {
            dp[j] = min(dp[j], dp[h[a[u]]-1] + c[u]);
        }
        for (int j = h[u] - 1; j >= 1; j--) {
            dp[j] = min(dp[j], dp[j+1]);
        }
    }

    ll ans = INF;
    for (int i = 1; i <= 1000000000; i++) {
        ans = min(ans, dp[i]);
    }

    printf("%lld\n", ans);

    return 0;
}