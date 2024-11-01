#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

typedef struct Edge {
    int to, next, weight;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], tot;
int n, m, q;
int order[MAXN];
int limit[MAXN];
int train[MAXN];
int maxflow, source, sink;

void addEdge(int u, int v, int w) {
    edges[tot].to = v;
    edges[tot].weight = w;
    edges[tot].next = head[u];
    head[u] = tot++;
}

void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int dfs(int u, int flow) {
    if (u == sink) {
        maxflow += flow;
        return flow;
    }
    int used = 0;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        int w = edges[i].weight;
        if (w > 0) {
            int d = dfs(v, min(flow - used, w));
            if (d > 0) {
                edges[i].weight -= d;
                edges[i ^ 1].weight += d;
                used += d;
            }
            if (used == flow) {
                break;
            }
        }
    }
    return used;
}

void Dinic() {
    while (1) {
        maxflow = 0;
        if (dfs(source, 0x7fffffff) == 0) {
            break;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    init();
    source = 0;
    sink = n + 1;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &order[i]);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", &limit[i]);
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    for (int i = 0; i < q; i++) {
        int city;
        scanf("%d", &city);
        train[city] = 1;
    }

    int current_gold = 0;

    for (int i = 1; i <= n; i++) {
        int city = order[i];
        if (limit[city] > 0) {
            current_gold += limit[city];
        } else {
            int max_sell = -limit[city];
            int min_gold = current_gold - max_sell;
            if (train[city]) {
                addEdge(source, city, 0x7fffffff);
                addEdge(city, source, 0);
            }
            for (int j = head[city]; j != -1; j = edges[j].next) {
                int v = edges[j].to;
                int w = edges[j].weight;
                if (w > min_gold) {
                    addEdge(city, v, w - min_gold);
                    addEdge(v, city, min_gold);
                }
            }
            Dinic();
            int sell_amount = current_gold - maxflow;
            printf("%d\n", sell_amount);
            current_gold = maxflow;
        }
    }

    return 0;
}