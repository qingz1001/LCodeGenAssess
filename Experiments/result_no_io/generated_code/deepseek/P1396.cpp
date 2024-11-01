#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 10001
#define MAXM 20001
#define INF 1000000000

typedef struct {
    int v, w;
} Edge;

typedef struct {
    Edge edges[MAXM];
    int head[MAXN];
    int next[MAXM];
    int cnt;
} Graph;

Graph g;
bool visited[MAXN];

void add_edge(int u, int v, int w) {
    g.edges[g.cnt].v = v;
    g.edges[g.cnt].w = w;
    g.next[g.cnt] = g.head[u];
    g.head[u] = g.cnt++;
}

bool dfs(int u, int t, int max_w) {
    if (u == t) return true;
    visited[u] = true;
    for (int i = g.head[u]; i != -1; i = g.next[i]) {
        int v = g.edges[i].v;
        int w = g.edges[i].w;
        if (!visited[v] && w <= max_w) {
            if (dfs(v, t, max_w)) return true;
        }
    }
    return false;
}

int binary_search(int n, int s, int t, int max_edge_w) {
    int left = 0, right = max_edge_w;
    while (left < right) {
        int mid = (left + right) / 2;
        for (int i = 1; i <= n; i++) visited[i] = false;
        if (dfs(s, t, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);

    for (int i = 1; i <= n; i++) g.head[i] = -1;
    g.cnt = 0;

    int max_edge_w = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
        if (w > max_edge_w) max_edge_w = w;
    }

    int result = binary_search(n, s, t, max_edge_w);
    printf("%d\n", result);

    return 0;
}