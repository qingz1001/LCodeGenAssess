#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1500005

int n, q, x[MAXN], y[MAXN], z[MAXN], a[MAXN], cnt[MAXN], ans[MAXN], flag[MAXN];

void dfs(int u) {
    int sum = cnt[u];
    if (x[u] != 0) sum += cnt[x[u]];
    if (y[u] != 0) sum += cnt[y[u]];
    if (z[u] != 0) sum += cnt[z[u]];
    ans[u] = (sum > 1);
    if (x[u] != 0) cnt[x[u]] = ans[u];
    if (y[u] != 0) cnt[y[u]] = ans[u];
    if (z[u] != 0) cnt[z[u]] = ans[u];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &x[i], &y[i], &z[i]);
    }
    for (int i = 1; i <= 3 * n + 1; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= 3 * n + 1; i++) {
        if (a[i]) flag[i] = 1;
    }
    for (int i = 1; i <= 3 * n + 1; i++) {
        if (flag[i]) {
            cnt[i] = 1;
            dfs(i);
        }
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int x;
        scanf("%d", &x);
        flag[x] ^= 1;
        if (flag[x]) {
            cnt[x] = 1;
            dfs(x);
        } else {
            cnt[x] = 0;
            dfs(x);
        }
        printf("%d\n", ans[1]);
    }
    return 0;
}