#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005

typedef struct {
    int v;
    struct Edge* next;
} Edge;

Edge* graph[MAXN];
bool visited[MAXN];
int parent[MAXN];
int low[MAXN];
int disc[MAXN];
int time;
int n, m;

void addEdge(int u, int v) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->v = v;
    newEdge->next = graph[u];
    graph[u] = newEdge;
}

void dfs(int u) {
    visited[u] = true;
    disc[u] = low[u] = ++time;
    int children = 0;

    for (Edge* e = graph[u]; e != NULL; e = e->next) {
        int v = e->v;
        if (!visited[v]) {
            children++;
            parent[v] = u;
            dfs(v);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
        } else if (v != parent[u]) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

bool isBiconnected(int u, int v) {
    if (u == v) return false;
    if (parent[v] == u) return true;
    return false;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    int count = 0;
    for (int u = 1; u <= n; u++) {
        for (int v = u + 1; v <= n; v++) {
            if (isBiconnected(u, v)) {
                count++;
            }
        }
    }

    printf("%d\n", count);

    for (int i = 1; i <= n; i++) {
        Edge* e = graph[i];
        while (e != NULL) {
            Edge* next = e->next;
            free(e);
            e = next;
        }
    }

    return 0;
}