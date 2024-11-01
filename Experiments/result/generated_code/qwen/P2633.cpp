#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define INF 0x3f3f3f3f

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count;
int n, m;
int weights[MAXN];
int last = 0;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int dfs(int node, int parent, int k) {
    if (node == v) return weights[node];
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int child = edges[i].to;
        if (child != parent) {
            int result = dfs(child, node, k);
            if (result != INF) {
                return result;
            }
        }
    }
    return INF;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &weights[i]);
    }
    memset(head, -1, sizeof(head));
    edge_count = 0;
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }

    int u, v, k;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &k);
        if (i == 0) {
            printf("%d\n", dfs(u, -1, k));
        } else {
            printf("%d\n", dfs(u, -1, k));
        }
    }

    return 0;
}