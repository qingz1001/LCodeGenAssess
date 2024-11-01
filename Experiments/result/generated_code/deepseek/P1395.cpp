#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005

typedef struct Edge {
    int to, next;
} Edge;

Edge edges[2 * MAXN];
int head[MAXN], cnt = 0;
int n;
int size[MAXN], dist[MAXN];

void addEdge(int u, int v) {
    edges[cnt].to = v;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u, int parent) {
    size[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        dfs(v, u);
        size[u] += size[v];
        dist[u] += dist[v] + size[v];
    }
}

void dfs2(int u, int parent, int totalSize) {
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        dist[v] = dist[u] - size[v] + (totalSize - size[v]);
        dfs2(v, u, totalSize);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        dist[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }

    dfs(1, -1);
    dfs2(1, -1, n);

    int minDist = dist[1], minNode = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] < minDist || (dist[i] == minDist && i < minNode)) {
            minDist = dist[i];
            minNode = i;
        }
    }

    printf("%d %d\n", minNode, minDist);
    return 0;
}