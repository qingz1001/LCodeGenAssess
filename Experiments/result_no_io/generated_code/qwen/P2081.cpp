#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int to, weight;
} Edge;

int n, m;
Edge edges[MAXN];
int degree[MAXN];
double dp[MAXN];

void dfs(int u, int parent) {
    for (int i = 0; i < degree[u]; ++i) {
        if (edges[i].to == parent) continue;
        int v = edges[i].to;
        int w = edges[i].weight;
        dp[v] += dp[u] + w - w * degree[v] / degree[u];
        dfs(v, u);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        --x, --y;
        edges[i].to = y, edges[i].weight = w;
        edges[m + i].to = x, edges[m + i].weight = w;
        degree[x]++;
        degree[y]++;
    }

    dp[0] = 0;
    dfs(0, -1);

    double total_length = 0;
    for (int i = 0; i < n; ++i) {
        total_length += dp[i] * degree[i];
    }

    printf("%.5f\n", total_length / n);

    return 0;
}