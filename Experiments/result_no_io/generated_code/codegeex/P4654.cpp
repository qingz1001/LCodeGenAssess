#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000001

int n, t, m;
int parent[MAXN];
int depth[MAXN];
int subtree_size[MAXN];
int max_depth[MAXN];
int heavy[MAXN];
int head[MAXN];
int next[MAXN * 2];
int to[MAXN * 2];
int edge_count;

void add_edge(int u, int v) {
    next[edge_count] = head[u];
    head[u] = edge_count;
    to[edge_count] = v;
    edge_count++;
}

void dfs1(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    subtree_size[u] = 1;
    int max_subtree_size = 0;
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = to[i];
        if (v == p) continue;
        dfs1(v, u);
        subtree_size[u] += subtree_size[v];
        if (subtree_size[v] > max_subtree_size) {
            max_subtree_size = subtree_size[v];
            heavy[u] = v;
        }
    }
}

void dfs2(int u, int h) {
    head[u] = -1;
    heavy[u] = h;
    if (heavy[u]) {
        max_depth[u] = max_depth[heavy[u]] + 1;
        dfs2(heavy[u], h);
    }
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = to[i];
        if (v == heavy[u]) continue;
        max_depth[u] = max(max_depth[u], max_depth[v] + 1);
        dfs2(v, v);
    }
}

int main() {
    scanf("%d%d%d", &n, &t, &m);
    memset(head, -1, sizeof(head));
    edge_count = 0;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    int result = max_depth[m];
    for (int u = m; u != t; u = parent[u]) {
        int v = heavy[u];
        if (v && max_depth[v] + 1 >= max_depth[parent[u]]) {
            result += 2;
        } else {
            result++;
        }
    }
    printf("%d\n", result);
    return 0;
}