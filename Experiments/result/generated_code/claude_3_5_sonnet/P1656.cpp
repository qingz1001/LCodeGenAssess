#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 151
#define MAX_M 5001

int n, m;
int graph[MAX_N][MAX_N];
int visited[MAX_N];
int low[MAX_N], dfn[MAX_N];
int parent[MAX_N];
int timestamp;

typedef struct {
    int a, b;
} Edge;

Edge bridges[MAX_M];
int bridge_count = 0;

void dfs(int u) {
    visited[u] = 1;
    dfn[u] = low[u] = ++timestamp;
    
    for (int v = 1; v <= n; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                parent[v] = u;
                dfs(v);
                if (low[v] > dfn[u]) {
                    if (u < v) {
                        bridges[bridge_count].a = u;
                        bridges[bridge_count].b = v;
                    } else {
                        bridges[bridge_count].a = v;
                        bridges[bridge_count].b = u;
                    }
                    bridge_count++;
                }
                if (low[v] < low[u]) {
                    low[u] = low[v];
                }
            } else if (v != parent[u] && dfn[v] < low[u]) {
                low[u] = dfn[v];
            }
        }
    }
}

int compare(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    if (e1->a != e2->a) {
        return e1->a - e2->a;
    }
    return e1->b - e2->b;
}

int main() {
    scanf("%d %d", &n, &m);
    
    memset(graph, 0, sizeof(graph));
    memset(visited, 0, sizeof(visited));
    memset(parent, -1, sizeof(parent));
    
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = graph[b][a] = 1;
    }
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    
    qsort(bridges, bridge_count, sizeof(Edge), compare);
    
    for (int i = 0; i < bridge_count; i++) {
        printf("%d %d\n", bridges[i].a, bridges[i].b);
    }
    
    return 0;
}