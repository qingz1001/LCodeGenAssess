#include <stdio.h>
#include <stdlib.h>

#define MAXN 200010
#define LL long long

int T, n, K, L;
LL a[MAXN], b[MAXN];
LL ans[MAXN];

void solve() {
    for (int i = 0; i < n; i++) {
        ans[i] = a[i] + b[i];
    }
    qsort(ans, n, sizeof(LL), cmp);
    LL sum = 0;
    for (int i = 0; i < K; i++) {
        sum += ans[n - 1 - i];
    }
    printf("%lld\n", sum);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &K, &L);
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%lld", &b[i]);
        }
        solve();
    }
    return 0;
}