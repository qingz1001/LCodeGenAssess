#include <stdio.h>
#include <stdlib.h>

#define MAXN 50000

int n;
int head[MAXN + 1], next[MAXN * 2 + 1], to[MAXN * 2 + 1], tot;
int dp[MAXN + 1], size[MAXN + 1];

void add(int u, int v) {
    to[++tot] = v;
    next[tot] = head[u];
    head[u] = tot;
}

void dfs(int u, int fa) {
    size[u] = 1;
    for (int i = head[u]; i; i = next[i]) {
        int v = to[i];
        if (v != fa) {
            dfs(v, u);
            size[u] += size[v];
            dp[u] += dp[v] + size[v];
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    int minn = 0x7fffffff, ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] < minn) {
            minn = dp[i];
            ans = i;
        }
    }
    printf("%d %d\n", ans, minn);
    return 0;
}