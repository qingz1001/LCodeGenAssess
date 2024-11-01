#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005
#define INF 1e9

typedef struct Edge {
    int to, next, w;
} Edge;

Edge edges[MAXN << 1];
int head[MAXN], edge_num;
int n, k;

void add_edge(int from, int to, int w) {
    edges[edge_num].to = to;
    edges[edge_num].next = head[from];
    edges[edge_num].w = w;
    head[from] = edge_num++;
}

int dfs(int u, int fa, int k, long long *gain, long long *cost) {
    if (k == 0) {
        *gain = *cost = 0;
        return 0;
    }
    int max_gain = -INF, max_cost = -INF;
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == fa) continue;
        long long sub_gain, sub_cost;
        int sub_k = k - (edges[i].w >= 0);
        dfs(v, u, sub_k, &sub_gain, &sub_cost);
        if (edges[i].w >= 0) {
            gain[u] += sub_gain + edges[i].w;
            cost[u] += sub_cost;
        } else {
            gain[u] += sub_gain;
            cost[u] += sub_cost - edges[i].w;
        }
        if (sub_gain > max_gain) {
            max_gain = sub_gain;
        }
        if (sub_cost > max_cost) {
            max_cost = sub_cost;
        }
    }
    if (max_gain != -INF) {
        gain[u] -= max_gain;
    }
    if (max_cost != -INF) {
        cost[u] -= max_cost;
    }
    return 0;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n - 1; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        add_edge(x, y, w);
        add_edge(y, x, w);
    }
    long long gain[MAXN], cost[MAXN];
    dfs(1, 0, k, gain, cost);
    printf("%lld\n", gain[1]);
    return 0;
}