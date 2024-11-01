#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 150
#define MAXM 5000

typedef struct {
    int a, b;
} Edge;

Edge edges[MAXM];
bool visited[MAXN];
int adj[MAXN][MAXN];
int n, m;

void dfs(int u) {
    visited[u] = true;
    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v);
        }
    }
}

bool is_connected() {
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    dfs(0);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

int compare(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    if (e1->a == e2->a) {
        return e1->b - e2->b;
    }
    return e1->a - e2->a;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i].a, &edges[i].b);
        edges[i].a--;
        edges[i].b--;
        adj[edges[i].a][edges[i].b] = 1;
        adj[edges[i].b][edges[i].a] = 1;
    }

    Edge key_roads[MAXM];
    int key_count = 0;

    for (int i = 0; i < m; i++) {
        int u = edges[i].a;
        int v = edges[i].b;
        adj[u][v] = 0;
        adj[v][u] = 0;

        if (!is_connected()) {
            if (u < v) {
                key_roads[key_count].a = u + 1;
                key_roads[key_count].b = v + 1;
            } else {
                key_roads[key_count].a = v + 1;
                key_roads[key_count].b = u + 1;
            }
            key_count++;
        }

        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    qsort(key_roads, key_count, sizeof(Edge), compare);

    for (int i = 0; i < key_count; i++) {
        printf("%d %d\n", key_roads[i].a, key_roads[i].b);
    }

    return 0;
}