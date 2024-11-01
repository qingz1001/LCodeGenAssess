#include <stdio.h>
#include <stdlib.h>

#define MAXN 150
#define MAXM 5000

typedef struct {
    int a, b;
} Edge;

Edge edges[MAXM];
int adj[MAXN][MAXN];
int visited[MAXN];
int n, m;

void dfs(int u) {
    visited[u] = 1;
    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v);
        }
    }
}

int isConnected() {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    dfs(0);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return 0;
        }
    }
    return 1;
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

    Edge keyRoads[MAXM];
    int keyRoadCount = 0;

    for (int i = 0; i < m; i++) {
        int u = edges[i].a;
        int v = edges[i].b;
        adj[u][v] = 0;
        adj[v][u] = 0;

        if (!isConnected()) {
            if (u < v) {
                keyRoads[keyRoadCount].a = u + 1;
                keyRoads[keyRoadCount].b = v + 1;
            } else {
                keyRoads[keyRoadCount].a = v + 1;
                keyRoads[keyRoadCount].b = u + 1;
            }
            keyRoadCount++;
        }

        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    qsort(keyRoads, keyRoadCount, sizeof(Edge), compare);

    for (int i = 0; i < keyRoadCount; i++) {
        printf("%d %d\n", keyRoads[i].a, keyRoads[i].b);
    }

    return 0;
}