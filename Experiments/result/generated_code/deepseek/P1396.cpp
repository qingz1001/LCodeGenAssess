#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 10005
#define MAXM 20005
#define INF 1000000000

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
bool visited[MAXN];
int n, m, s, t;

void add_edge(int u, int v, int w) {
    edges[edge_count].v = v;
    edges[edge_count].w = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

bool dfs(int u, int max_w) {
    if (u == t) return true;
    visited[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        int w = edges[i].w;
        if (!visited[v] && w <= max_w) {
            if (dfs(v, max_w)) return true;
        }
    }
    return false;
}

bool can_reach(int max_w) {
    for (int i = 1; i <= n; i++) visited[i] = false;
    return dfs(s, max_w);
}

int main() {
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    int left = 0, right = INF;
    while (left < right) {
        int mid = (left + right) / 2;
        if (can_reach(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);
    return 0;
}