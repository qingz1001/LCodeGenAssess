#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAXN 200001
#define MOD 786433

int n, a[MAXN], deg[MAXN], dp[MAXN];
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot;

void add(int x, int y) {
    nxt[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
}

void dfs(int x, int fa) {
    dp[x] = a[x];
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y == fa) continue;
        dfs(y, x);
        dp[x] &= dp[y];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
        deg[x]++;
        deg[y]++;
    }
    dfs(1, 0);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + (long long)dp[i] * dp[i] % MOD) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}