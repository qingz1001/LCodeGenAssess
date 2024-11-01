#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 500005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], price[MAXN], min_price[MAXN], max_price[MAXN], vis[MAXN];
int n, m, edge_count;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs_min(int u) {
    vis[u] = 1;
    min_price[u] = price[u];
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!vis[v]) dfs_min(v);
        if (min_price[v] < min_price[u]) min_price[u] = min_price[v];
    }
}

void dfs_max(int u) {
    vis[u] = 1;
    max_price[u] = price[u];
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!vis[v]) dfs_max(v);
        if (max_price[v] > max_price[u]) max_price[u] = max_price[v];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
        head[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add_edge(x, y);
        if (z == 2) add_edge(y, x);
    }

    for (int i = 1; i <= n; i++) {
        min_price[i] = INT_MAX;
        max_price[i] = INT_MIN;
        vis[i] = 0;
    }

    dfs_min(1);

    for (int i = 1; i <= n; i++) vis[i] = 0;

    dfs_max(n);

    int max_profit = 0;
    for (int i = 1; i <= n; i++) {
        int profit = max_price[i] - min_price[i];
        if (profit > max_profit) max_profit = profit;
    }

    printf("%d\n", max_profit);

    return 0;
}