#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500005

struct Edge {
    int to;
    int weight;
    int next;
};

int n, s, cnt, head[MAXN];
struct Edge edges[MAXN * 2];
int depth[MAXN], subtree_size[MAXN], max_depth[MAXN], ans;

void add_edge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs1(int u, int parent) {
    subtree_size[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        depth[v] = depth[u] + edges[i].weight;
        max_depth[v] = depth[v];
        dfs1(v, u);
        subtree_size[u] += subtree_size[v];
        if (max_depth[u] < max_depth[v]) {
            max_depth[u] = max_depth[v];
        }
    }
}

void dfs2(int u, int parent) {
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        if (max_depth[v] == max_depth[u]) {
            ans += max_depth[v] - depth[v];
        }
        dfs2(v, u);
    }
}

int main() {
    scanf("%d %d", &n, &s);
    cnt = 0;
    memset(head, -1, sizeof(head));
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    depth[s] = 0;
    dfs1(s, -1);
    dfs2(s, -1);

    printf("%d\n", ans);
    return 0;
}