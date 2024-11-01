#include <stdio.h>
#include <stdlib.h>

#define MAX_N 7000
#define MAX_M 20000
#define INF 1e9

typedef struct {
    int to, v, p;
} Edge;

int n, m;
Edge edges[MAX_M];
int head[MAX_N], cnt = 0;

void add_edge(int u, int v, int w, int p) {
    edges[cnt].to = v;
    edges[cnt].v = w;
    edges[cnt].p = p;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

double max_ratio = -1.0;

void dfs(int u, double v_sum, double p_sum, int parent) {
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        dfs(v, v_sum + edges[i].v, p_sum + edges[i].p, u);
    }
    if (parent == -1) {
        max_ratio = fmax(max_ratio, v_sum / p_sum);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w, p;
        scanf("%d %d %d %d", &u, &v, &w, &p);
        add_edge(u, v, w, p);
    }

    for (int i = 1; i <= n; i++) {
        dfs(i, 0, 0, -1);
    }

    printf("%.1f\n", max_ratio);

    return 0;
}