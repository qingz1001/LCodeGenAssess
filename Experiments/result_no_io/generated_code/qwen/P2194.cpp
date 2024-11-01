#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef struct {
    int to, next;
} Edge;

Edge edges[600000];
int head[100005], edge_count = 0;
int n, m;
long long w[100005];
long long dp[100005][2];
int path[100005];

void add_edge(int from, int to) {
    edges[edge_count].to = to;
    edges[edge_count].next = head[from];
    head[from] = edge_count++;
}

void dfs(int u, int p) {
    dp[u][0] = 0;
    dp[u][1] = w[u];
    for (int e = head[u]; ~e; e = edges[e].next) {
        int v = edges[e].to;
        if (v == p) continue;
        dfs(v, u);
        dp[u][0] += dp[v][0];
        dp[u][1] += dp[v][1];
        if (dp[v][0] + w[u] < dp[v][1]) {
            dp[v][1] = dp[v][0] + w[u];
            path[v] = u;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &w[i]);
        head[i] = -1;
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
    }

    long long min_cost = LLONG_MAX;
    int start = -1;
    for (int i = 1; i <= n; i++) {
        dfs(i, -1);
        if (dp[i][1] < min_cost) {
            min_cost = dp[i][1];
            start = i;
        }
    }

    long long total_cost = 0;
    int count = 0;
    while (start != -1) {
        total_cost += w[start];
        count++;
        start = path[start];
    }

    printf("%lld %d\n", total_cost, count);

    return 0;
}