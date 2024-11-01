#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MOD 10007

int n, k;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], cnt;
long long dp[MAXN][151], size[MAXN], ans[MAXN];

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

long long quick_pow(long long base, int exp) {
    long long res = 1;
    while (exp) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

void dfs1(int u, int fa) {
    size[u] = 1;
    dp[u][0] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs1(v, u);
        for (int j = 0; j < k; j++)
            dp[u][j + 1] = (dp[u][j + 1] + dp[v][j]) % MOD;
        size[u] += size[v];
    }
}

void dfs2(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        for (int j = k; j > 0; j--)
            dp[v][j] = (dp[v][j - 1] + dp[u][j] - dp[v][j - 1] + MOD) % MOD;
        dp[v][0] = (dp[u][0] + MOD - dp[v][0] + 1) % MOD;
        dfs2(v, u);
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    dfs1(1, 0);
    dfs2(1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++)
            ans[i] = (ans[i] + dp[i][j] * quick_pow(j, k)) % MOD;
    }

    for (int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);

    return 0;
}