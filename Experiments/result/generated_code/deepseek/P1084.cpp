#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50005

typedef struct {
    int to, weight;
} Edge;

typedef struct {
    int id, dist;
} Army;

int n, m;
int army[MAXN];
Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int depth[MAXN], parent[MAXN][20], max_depth = 0;
int dist[MAXN];

void add_edge(int u, int v, int w) {
    edges[edge_count].to = v;
    edges[edge_count].weight = w;
    edges[edge_count + 1].to = u;
    edges[edge_count + 1].weight = w;
    head[u] = edge_count++;
    head[v] = edge_count++;
}

void dfs(int u, int p, int d) {
    depth[u] = depth[p] + 1;
    parent[u][0] = p;
    dist[u] = d;
    max_depth = (depth[u] > max_depth) ? depth[u] : max_depth;
    for (int i = head[u]; i != -1; i = edges[i].to) {
        int v = edges[i].to;
        if (v != p) {
            dfs(v, u, d + edges[i].weight);
        }
    }
}

void init_lca() {
    for (int j = 1; (1 << j) <= max_depth; j++) {
        for (int i = 1; i <= n; i++) {
            if (parent[i][j - 1] != -1) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
            }
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    int log;
    for (log = 1; (1 << log) <= depth[u]; log++);
    log--;
    for (int i = log; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = parent[u][i];
        }
    }
    if (u == v) return u;
    for (int i = log; i >= 0; i--) {
        if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

int compare(const void *a, const void *b) {
    return ((Army *)a)->dist - ((Army *)b)->dist;
}

int check(int limit) {
    Army armies[MAXN];
    int count = 0;
    for (int i = 0; i < m; i++) {
        int u = army[i];
        int d = 0;
        for (int j = 19; j >= 0; j--) {
            if (parent[u][j] > 1 && d + dist[u] - dist[parent[u][j]] <= limit) {
                d += dist[u] - dist[parent[u][j]];
                u = parent[u][j];
            }
        }
        if (u != 1 && d + dist[u] <= limit) {
            armies[count].id = u;
            armies[count].dist = limit - dist[u];
            count++;
        }
    }
    qsort(armies, count, sizeof(Army), compare);
    int j = 0;
    for (int i = 0; i < count; i++) {
        if (armies[i].dist < dist[armies[j].id] && parent[armies[i].id][0] != armies[j].id) {
            j++;
        }
    }
    return j == count;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &army[i]);
    }
    dfs(1, 0, 0);
    init_lca();
    int left = 0, right = INT_MAX, ans = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}