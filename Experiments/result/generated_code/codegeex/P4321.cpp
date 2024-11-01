#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define MAXN 19
#define MAXE 324
#define MOD 998244353

int n, m;
int u[MAXE], v[MAXE];
int e[MAXN], nxt[MAXE], head[MAXN], edgecnt;
int s;
int p[MAXN], q[MAXN];
int dp[MAXN][1 << 18];

void add_edge(int x, int y) {
    u[edgecnt] = x;
    v[edgecnt] = y;
    nxt[edgecnt] = head[x];
    head[x] = edgecnt++;
}

int dfs(int x, int mask) {
    if (dp[x][mask] != -1) return dp[x][mask];
    if (mask == (1 << s) - 1) return dp[x][mask] = 0;
    dp[x][mask] = 0;
    for (int i = head[x]; i != -1; i = nxt[i]) {
        int y = v[i];
        if (mask & (1 << (y - 1))) continue;
        dp[x][mask] = (dp[x][mask] + dfs(y, mask | (1 << (y - 1)))) % MOD;
    }
    return dp[x][mask];
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    scanf("%d", &m);
    while (m--) {
        int k, x, ans = 0;
        scanf("%d", &k);
        for (int i = 0; i < k; i++) scanf("%d", &p[i]);
        scanf("%d", &x);
        s = 0;
        for (int i = 0; i < k; i++) q[s++] = p[i];
        q[s++] = x;
        memset(dp, -1, sizeof(dp));
        dfs(x, 1 << (x - 1));
        for (int i = 0; i < s; i++) {
            for (int j = 0; j < s; j++) {
                if (i == j) continue;
                int mask = 0;
                for (int l = 0; l < s; l++) {
                    if (l == i || l == j) continue;
                    mask |= 1 << (p[l] - 1);
                }
                ans = (ans + 1ll * dp[p[i] - 1][mask] * dp[p[j] - 1][mask] % MOD) % MOD;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}