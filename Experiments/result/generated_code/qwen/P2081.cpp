#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int to, w;
    struct Edge *next;
} Edge;

Edge edges[MAXN << 1];
int head[MAXN], edgeIndex;

void addEdge(int u, int v, int w) {
    edges[edgeIndex].to = v;
    edges[edgeIndex].w = w;
    edges[edgeIndex].next = head[u];
    head[u] = &edges[edgeIndex++];
}

double dfs(int u, int parent, double totalLength, int visited[]) {
    if (visited[u]) return 0;
    visited[u] = 1;
    
    double sum = 0, count = 0;
    for (Edge *e = head[u]; e != NULL; e = e->next) {
        if (e->to == parent) continue;
        sum += dfs(e->to, u, totalLength + e->w, visited);
        count++;
    }
    
    if (count == 0) return totalLength;
    return (sum + totalLength) / count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        addEdge(x - 1, y - 1, w);
        addEdge(y - 1, x - 1, w);
    }
    
    double totalExpectation = 0;
    for (int i = 0; i < n; i++) {
        int visited[MAXN] = {0};
        totalExpectation += dfs(i, -1, 0, visited);
    }
    
    printf("%.6f\n", totalExpectation / n);
    return 0;
}