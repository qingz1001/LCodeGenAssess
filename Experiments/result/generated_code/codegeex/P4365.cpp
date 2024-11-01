#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 64123
#define MAXN 100005
#define MAXM 200005

int n, k, w, d[MAXN], head[MAXM], tot, ans;
struct Edge {
    int to, next;
} e[MAXM];

void addEdge(int u, int v) {
    e[tot].to = v;
    e[tot].next = head[u];
    head[u] = tot++;
}

int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int dp[MAXN][MAXN];

void dfs(int u, int fa) {
    int i, j, s = 0;
    for (i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u);
        for (j = s + k; j >= s; --j) {
            dp[u][j] = (dp[u][j] + dp[v][j - s]) % MOD;
        }
        s += k;
    }
    if (d[u] <= w) {
        for (i = 0; i <= s; ++i) {
            dp[u][i] = (dp[u][i] + dp[u][i - 1]) % MOD;
        }
        for (i = 1; i <= s; ++i) {
            dp[u][i] = (dp[u][i] + dp[u][i - 1]) % MOD;
        }
    } else {
        for (i = 0; i <= s; ++i) {
            dp[u][i] = dp[u][i - 1];
        }
    }
    if (s >= k) {
        for (i = k; i <= s; ++i) {
            ans = (ans + dp[u][i]) % MOD;
        }
    }
}

int main() {
    int i, u, v;
    scanf("%d %d %d", &n, &k, &w);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &d[i]);
    }
    memset(head, -1, sizeof(head));
    for (i = 1; i < n; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    qsort(d + 1, n, sizeof(int), cmp);
    dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}