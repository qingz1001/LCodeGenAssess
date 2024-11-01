#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXE 500005

int n, e, q;
int dfn[MAXN], low[MAXN], parent[MAXN], dfs_clock;
int head[MAXN], to[MAXE * 2], nxt[MAXE * 2], edge_cnt;

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

void tarjan(int u) {
    int child = 0;
    dfn[u] = low[u] = ++dfs_clock;
    for (int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            child++;
            parent[v] = u;
            tarjan(v);
            low[u] = low[u] < low[v] ? low[u] : low[v];
        } else if (v != parent[u]) {
            low[u] = low[u] < dfn[v] ? low[u] : dfn[v];
        }
    }
}

int query1(int a, int b, int g1, int g2) {
    if (parent[g1] == g2) {
        int t = g1;
        g1 = g2;
        g2 = t;
    }
    if (parent[g2] != g1) return 1;
    if (low[g2] <= dfn[g1]) return 1;
    if ((dfn[a] < dfn[g2] || dfn[a] > dfn[g2] + (dfn[n] - dfn[g2] + 1) / 2) &&
        (dfn[b] < dfn[g2] || dfn[b] > dfn[g2] + (dfn[n] - dfn[g2] + 1) / 2))
        return 1;
    return 0;
}

int query2(int a, int b, int c) {
    if (a == c || b == c) return 0;
    if ((dfn[a] < dfn[c] || dfn[a] > dfn[c] + (dfn[n] - dfn[c] + 1) / 2) &&
        (dfn[b] < dfn[c] || dfn[b] > dfn[c] + (dfn[n] - dfn[c] + 1) / 2))
        return 1;
    return 0;
}

int main() {
    scanf("%d%d", &n, &e);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    tarjan(1);
    scanf("%d", &q);
    while (q--) {
        int type, a, b, c, g1, g2;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d%d%d%d", &a, &b, &g1, &g2);
            printf("%s\n", query1(a, b, g1, g2) ? "yes" : "no");
        } else {
            scanf("%d%d%d", &a, &b, &c);
            printf("%s\n", query2(a, b, c) ? "yes" : "no");
        }
    }
    return 0;
}