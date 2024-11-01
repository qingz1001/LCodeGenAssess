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

void dfs(int u, int* price_array) {
    vis[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!vis[v]) {
            price_array[v] = price_array[u];
            dfs(v, price_array);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
        head[i] = -1;
        min_price[i] = INT_MAX;
        max_price[i] = INT_MIN;
    }

    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add_edge(x, y);
        if (z == 2) add_edge(y, x);
    }

    min_price[1] = price[1];
    dfs(1, min_price);

    for (int i = 1; i <= n; i++) vis[i] = 0;
    max_price[n] = price[n];
    dfs(n, max_price);

    int max_profit = 0;
    for (int i = 1; i <= n; i++) {
        if (min_price[i] != INT_MAX && max_price[i] != INT_MIN) {
            int profit = max_price[i] - min_price[i];
            if (profit > max_profit) max_profit = profit;
        }
    }

    printf("%d\n", max_profit);
    return 0;
}