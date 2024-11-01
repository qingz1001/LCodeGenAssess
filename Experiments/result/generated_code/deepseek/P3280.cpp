#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 200005

typedef struct {
    int to, weight;
} Edge;

typedef struct {
    Edge edges[MAXM];
    int head[MAXN], cnt;
} Graph;

Graph g;
int n, m, q;
int order[MAXN], b[MAXN];
int station[MAXN];
int max_weight[MAXN];

void add_edge(int u, int v, int w) {
    g.edges[g.cnt].to = v;
    g.edges[g.cnt].weight = w;
    g.edges[g.cnt].next = g.head[u];
    g.head[u] = g.cnt++;
}

void dfs(int u, int parent, int max_w) {
    max_weight[u] = max_w;
    for (int i = g.head[u]; i != -1; i = g.edges[i].next) {
        int v = g.edges[i].to;
        int w = g.edges[i].weight;
        if (v != parent) {
            dfs(v, u, max_w < w ? max_w : w);
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &order[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    for (int i = 1; i <= q; i++) {
        scanf("%d", &station[i]);
    }

    // Initialize graph
    for (int i = 1; i <= n; i++) {
        g.head[i] = -1;
    }
    g.cnt = 0;

    // DFS to find max weight for each city
    dfs(1, -1, INT_MAX);

    int gold = 0;
    for (int i = 1; i <= n; i++) {
        int city = order[i];
        if (b[city] < 0) {
            int sell_amount = -b[city];
            if (sell_amount > gold) {
                sell_amount = gold;
            }
            printf("%d\n", sell_amount);
            gold -= sell_amount;
        } else {
            int buy_amount = b[city];
            if (buy_amount > max_weight[city] - gold) {
                buy_amount = max_weight[city] - gold;
            }
            gold += buy_amount;
        }
    }

    return 0;
}