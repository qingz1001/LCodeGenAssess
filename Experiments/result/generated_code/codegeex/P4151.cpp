#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 100005

struct Edge {
    int to, next;
    long long weight;
} edges[MAXM * 2];

int head[MAXN], edgeCount;
int parent[MAXN];
long long depth[MAXN], xorSum[MAXN], xorMax[MAXN];
int visited[MAXN];

void addEdge(int u, int v, long long w) {
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void dfs(int u, int p) {
    visited[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!visited[v]) {
            depth[v] = depth[u] + 1;
            xorSum[v] = xorSum[u] ^ edges[i].weight;
            parent[v] = find(u);
            dfs(v, u);
        }
    }
}

void findMaxXOR(int u) {
    visited[u] = 1;
    xorMax[u] = xorSum[u];
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!visited[v]) {
            findMaxXOR(v);
            xorMax[u] = xorMax[u] ^ xorMax[v];
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    depth[1] = 0;
    xorSum[1] = 0;
    parent[1] = 1;
    dfs(1, 0);

    memset(visited, 0, sizeof(visited));
    visited[1] = 1;
    findMaxXOR(1);

    printf("%lld\n", xorMax[1]);
    return 0;
}