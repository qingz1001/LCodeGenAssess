#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5000
#define MAXK 1000

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[MAXN+1];
int parent[MAXN+1];
int depth[MAXN+1];
int size[MAXN+1];
int pos[MAXN+1];
int cnt[MAXN+1];
int ans[MAXK][2];
int foodPos[MAXK];

void addEdge(int u, int v) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = v;
    e->next = adj[u];
    adj[u] = e;
}

void dfs(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    size[u] = 1;
    for (Edge* e = adj[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == p) continue;
        dfs(v, u);
        size[u] += size[v];
        if (size[v] > size[pos[u]]) pos[u] = v;
    }
}

void decompose(int u, int p) {
    static int rank = 0;
    cnt[rank++] = u;
    if (pos[u] != -1) decompose(pos[u], u);
    for (Edge* e = adj[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == p || v == pos[u]) continue;
        decompose(v, u);
    }
}

int lca(int u, int v) {
    while (depth[u] > depth[v]) u = parent[u];
    while (depth[v] > depth[u]) v = parent[v];
    while (u != v) {
        u = parent[u];
        v = parent[v];
    }
    return u;
}

int jump(int u, int d) {
    while (depth[u] - depth[d] > d) {
        u = parent[u];
    }
    return u;
}

void processFood(int food) {
    for (int i = 0; i < k; i++) {
        int u = foodPos[i];
        int v = food;
        int l = lca(u, v);
        int d = depth[u] + depth[v] - 2 * depth[l];
        if (d > 0) {
            u = jump(u, d);
        }
        ans[i][0] = u;
        ans[i][1]++;
    }
}

int main() {
    int n, h, k;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) adj[i] = NULL;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        int p;
        scanf("%d", &p);
        foodPos[i] = p;
    }
    scanf("%d", &h);
    for (int i = 0; i < h; i++) {
        int food;
        scanf("%d", &food);
        processFood(food);
    }
    for (int i = 0; i < k; i++) {
        printf("%d %d\n", ans[i][0], ans[i][1]);
    }
    return 0;
}