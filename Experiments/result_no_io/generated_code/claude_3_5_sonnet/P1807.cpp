#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1505
#define MAX_M 50005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to, weight;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
int dist[MAX_N];
int visited[MAX_N];
int n, m;

void addEdge(int from, int to, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->to = to;
    newEdge->weight = weight;
    newEdge->next = graph[from];
    graph[from] = newEdge;
}

int dfs(int u) {
    if (u == n) return 0;
    if (visited[u]) return dist[u];
    
    visited[u] = 1;
    int maxDist = -INF;
    
    for (Edge* e = graph[u]; e != NULL; e = e->next) {
        int v = e->to;
        int w = e->weight;
        int d = dfs(v);
        if (d != -INF && d + w > maxDist) {
            maxDist = d + w;
        }
    }
    
    dist[u] = maxDist;
    return maxDist;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }
    
    memset(dist, -1, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    
    int result = dfs(1);
    
    if (result == -INF) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }
    
    return 0;
}