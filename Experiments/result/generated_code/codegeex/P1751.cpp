#include <stdio.h>
#include <stdlib.h>

#define MAXN 5000
#define MAXK 1000

int n, k, h;
int parent[MAXN + 1], depth[MAXN + 1], size[MAXN + 1], heavy[MAXN + 1], head[MAXN + 1];
int chainCount, pos[MAXN + 1], rev[MAXN + 1];
int food[MAXN + 1], result[MAXK][2];

struct Edge {
    int to, next;
} edge[MAXN * 2];

void addEdge(int u, int v) {
    static int count = 0;
    edge[count].to = v;
    edge[count].next = head[u];
    head[u] = count++;
}

void dfs1(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    size[u] = 1;
    int maxSubtreeSize = 0;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (v == p) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > maxSubtreeSize) {
            maxSubtreeSize = size[v];
            heavy[u] = v;
        }
    }
}

void dfs2(int u, int h) {
    chainCount++;
    pos[u] = chainCount;
    rev[chainCount] = u;
    head[u] = -1;
    heavy[u] = h;
    if (heavy[u]) addEdge(h, u);
    if (heavy[u]) dfs2(heavy[u], h);
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (v == parent[u] || v == heavy[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (heavy[u] != heavy[v]) {
        if (depth[heavy[u]] > depth[heavy[v]]) u = parent[heavy[u]];
        else v = parent[heavy[v]];
    }
    return depth[u] < depth[v] ? u : v;
}

void processFood(int foodNode) {
    for (int i = 0; i < k; i++) {
        int snakeNode = food[i];
        if (depth[snakeNode] > depth[foodNode]) {
            int lcaNode = lca(snakeNode, foodNode);
            if (depth[lcaNode] == depth[snakeNode]) {
                result[i][0] = snakeNode;
                result[i][1]++;
            } else {
                result[i][0] = lcaNode;
                result[i][1]++;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        int p;
        scanf("%d", &p);
        food[i] = p;
    }
    scanf("%d", &h);
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 0; i < h; i++) {
        int foodNode;
        scanf("%d", &foodNode);
        processFood(foodNode);
    }
    for (int i = 0; i < k; i++) {
        printf("%d %d\n", result[i][0], result[i][1]);
    }
    return 0;
}