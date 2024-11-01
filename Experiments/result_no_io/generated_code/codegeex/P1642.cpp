#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100
#define MAXM (MAXN - 1)

int n, m;
int w[MAXN], c[MAXN];
int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], edge_cnt;

void add_edge(int u, int v) {
    nxt[edge_cnt] = head[u];
    to[edge_cnt] = v;
    head[u] = edge_cnt++;
}

struct Edge {
    int u, v;
    double w;
} edges[MAXM * 2];

int cmp(const void *a, const void *b) {
    return ((struct Edge *)b)->w - ((struct Edge *)a)->w;
}

double max_ratio = 0.0;

void dfs(int u, int fa, int cnt, double ratio) {
    if (cnt == m) {
        max_ratio = fmax(max_ratio, ratio);
        return;
    }
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u, cnt + 1, ratio * (double)(w[u] * c[v]) / (double)(w[v] * c[u]));
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", &w[i]);
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u - 1, v - 1);
        add_edge(v - 1, u - 1);
    }
    dfs(0, -1, 0, 1.0);
    printf("%.1f\n", max_ratio);
    return 0;
}