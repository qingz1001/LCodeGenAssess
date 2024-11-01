#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 7000
#define MAXM 20000

typedef struct {
    int to, v, p;
} Edge;

Edge edges[MAXM];
int n, m, e;
int head[MAXN], degree[MAXN];

double dfs(int u, double v_sum, double p_sum, int parent) {
    for (int i = head[u]; i != -1; i = edges[i].to) {
        if (edges[i].to == parent) continue;
        double new_v_sum = v_sum + edges[i].v;
        double new_p_sum = p_sum + edges[i].p;
        double result = dfs(edges[i].to, new_v_sum, new_p_sum, u);
        if (result > 0) return result;
    }
    if (degree[u] == 1 && parent != -1) {
        return (v_sum + edges[head[u]].v) / (p_sum + edges[head[u]].p);
    }
    return -1;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w, p;
        scanf("%d %d %d %d", &u, &v, &w, &p);
        edges[e++] = (Edge){v, w, p};
        head[v]++;
        degree[u]++;
    }

    double max_ratio = -1;
    for (int i = 1; i <= n; i++) {
        if (degree[i] >= 2) {
            max_ratio = fmax(max_ratio, dfs(i, 0, 0, -1));
        }
    }

    printf("%.1f\n", max_ratio);
    return 0;
}