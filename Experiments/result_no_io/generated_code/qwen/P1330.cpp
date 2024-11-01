#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define MAXM 200005

typedef struct {
    int v, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], degree[MAXN];
int visited[MAXN];

void add_edge(int u, int v) {
    edges[m].v = v;
    edges[m].next = head[u];
    head[u] = m++;
}

int dfs(int u, int parent) {
    if (visited[u]) return 0;
    visited[u] = 1;
    int count = 0;
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].v;
        if (v == parent) continue;
        count += dfs(v, u);
    }
    if (count == 0) return 1;
    return count / 2 + (count % 2);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u - 1, v - 1);
        add_edge(v - 1, u - 1);
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            result += dfs(i, -1);
        }
    }

    printf("%s\n", result ? "Possible" : "Impossible");
    return 0;
}