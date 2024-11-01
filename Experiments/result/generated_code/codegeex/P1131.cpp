#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500010

struct Edge {
    int to, next, weight;
} edges[MAXN * 2];

int head[MAXN], edgeCount;
int n, s;
long long minCost;

void addEdge(int u, int v, int w) {
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void dfs(int u, int parent, int depth) {
    int maxDepth = depth;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        dfs(v, u, depth + edges[i].weight);
        maxDepth = maxDepth > depth ? maxDepth : depth;
    }
    if (maxDepth != depth) {
        minCost += (long long)depth - maxDepth;
    }
}

int main() {
    scanf("%d %d", &n, &s);
    memset(head, -1, sizeof(head));
    edgeCount = 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    dfs(s, -1, 0);

    printf("%lld\n", minCost);
    return 0;
}