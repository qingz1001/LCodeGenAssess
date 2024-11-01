#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAXN 50000
#define MAXM 50000

typedef long long ll;

struct Edge {
    int to;
    int weight;
    struct Edge *next;
};

struct Army {
    int city;
    int time;
};

struct Edge *edges[MAXN];
int n, m;
int parent[MAXN];
int depth[MAXN];
int subtree_size[MAXN];
int heavy_child[MAXN];
int head[MAXN];
int pos[MAXN];
int cnt;
int army_count;
struct Army armies[MAXM];

void add_edge(int u, int v, int w) {
    struct Edge *e1 = (struct Edge *)malloc(sizeof(struct Edge));
    struct Edge *e2 = (struct Edge *)malloc(sizeof(struct Edge));
    e1->to = v;
    e1->weight = w;
    e1->next = edges[u];
    edges[u] = e1;
    e2->to = u;
    e2->weight = w;
    e2->next = edges[v];
    edges[v] = e2;
}

void dfs1(int u) {
    subtree_size[u] = 1;
    for (struct Edge *e = edges[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == parent[u]) continue;
        parent[v] = u;
        depth[v] = depth[u] + 1;
        dfs1(v);
        subtree_size[u] += subtree_size[v];
        if (subtree_size[v] > subtree_size[heavy_child[u]]) {
            heavy_child[u] = v;
        }
    }
}

void dfs2(int u, int h) {
    head[u] = h;
    pos[u] = ++cnt;
    if (heavy_child[u] != 0) {
        dfs2(heavy_child[u], h);
    }
    for (struct Edge *e = edges[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == parent[u] || v == heavy_child[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) {
            v = parent[head[v]];
        } else {
            u = parent[head[u]];
        }
    }
    if (depth[u] > depth[v]) {
        return v;
    } else {
        return u;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &armies[i].city);
    }

    dfs1(1);
    dfs2(1, 1);

    // TODO: Add your solution here

    return 0;
}