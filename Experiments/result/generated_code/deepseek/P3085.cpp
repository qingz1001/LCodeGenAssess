#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct Edge {
    int to, type;
    struct Edge *next;
} Edge;

Edge *newEdge(int to, int type) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->to = to;
    e->type = type;
    e->next = NULL;
    return e;
}

Edge *adj[MAXN];
int size[MAXN], color[MAXN], parent[MAXN], depth[MAXN];
int cnt[MAXN][2], pathCnt[MAXN][2];
int ans = 0;

void addEdge(int u, int v, int type) {
    Edge *e = newEdge(v, type);
    e->next = adj[u];
    adj[u] = e;
}

void dfs(int u, int p) {
    size[u] = 1;
    parent[u] = p;
    depth[u] = depth[p] + 1;
    for (Edge *e = adj[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == p) continue;
        color[v] = color[u] ^ e->type;
        dfs(v, u);
        size[u] += size[v];
    }
}

void dfs2(int u, int p) {
    for (Edge *e = adj[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == p) continue;
        dfs2(v, u);
        cnt[u][0] += cnt[v][0];
        cnt[u][1] += cnt[v][1];
    }
    cnt[u][color[u]]++;
    for (Edge *e = adj[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == p) continue;
        pathCnt[u][0] += pathCnt[v][0];
        pathCnt[u][1] += pathCnt[v][1];
    }
    if (cnt[u][0] == cnt[u][1]) ans++;
    for (Edge *e = adj[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == p) continue;
        if (cnt[v][0] == cnt[v][1]) pathCnt[u][color[u]]++;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        addEdge(a, b, t);
        addEdge(b, a, t);
    }
    dfs(1, 0);
    dfs2(1, 0);
    printf("%d\n", ans);
    return 0;
}