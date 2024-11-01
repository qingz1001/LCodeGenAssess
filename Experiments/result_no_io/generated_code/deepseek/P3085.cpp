#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct Edge {
    int to, type;
    struct Edge *next;
} Edge;

Edge edges[MAXN * 2];
Edge *head[MAXN];
int edge_cnt = 0;

void add_edge(int u, int v, int type) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].type = type;
    edges[edge_cnt].next = head[u];
    head[u] = &edges[edge_cnt++];
}

int n;
int balance[MAXN];
int subtree_balance[MAXN];
int subtree_size[MAXN];
int ans = 0;

void dfs(int u, int parent) {
    subtree_size[u] = 1;
    for (Edge *e = head[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == parent) continue;
        balance[v] = balance[u] + (e->type == 0 ? 1 : -1);
        dfs(v, u);
        subtree_size[u] += subtree_size[v];
        subtree_balance[u] += subtree_balance[v];
    }
    subtree_balance[u] += balance[u];
}

void solve(int u, int parent) {
    for (Edge *e = head[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == parent) continue;
        solve(v, u);
        if (subtree_balance[v] == 0) {
            ans += subtree_size[v] * (n - subtree_size[v]);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        add_edge(a, b, t);
        add_edge(b, a, t);
    }

    dfs(1, -1);
    solve(1, -1);

    printf("%d\n", ans);
    return 0;
}