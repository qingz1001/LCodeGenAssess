#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[100005];
int head[100005];
int degree[100005];
int dp[100005][151];
int dis[100005];

void add_edge(int from, int to) {
    edges[++edge_cnt].to = to;
    edges[edge_cnt].next = head[from];
    head[from] = edge_cnt;
}

void dfs(int u, int fa, int depth) {
    dis[u] = depth;
    for (int i = head[u]; i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == fa) continue;
        dfs(v, u, depth + 1);
    }
}

void calc(int u, int fa, int d, int sum) {
    dp[u][d] = (dp[u][d] + sum) % MOD;
    for (int i = head[u]; i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == fa) continue;
        calc(v, u, d + 1, sum + dis[v]);
    }
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    for (int i = 1; i <= n; ++i) {
        dfs(i, -1, 0);
        calc(i, -1, 0, 0);
    }

    for (int i = 1; i <= n; ++i) {
        long long res = 0;
        for (int d = 0; d <= k; ++d) {
            res += dp[i][d];
            res %= MOD;
        }
        printf("%lld\n", res);
    }

    return 0;
}