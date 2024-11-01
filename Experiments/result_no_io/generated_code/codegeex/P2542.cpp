#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005
#define MAXM 100005

typedef struct {
    int u, v, next;
} Edge;

int n, m, tot;
Edge edge[MAXM * 2];
int head[MAXN], dfn[MAXN], low[MAXN], stack[MAXN], top, index;
int belong[MAXN], cnt;
int in[MAXN], out[MAXN], ans[MAXN];
int parent[MAXN], size[MAXN];

void add_edge(int u, int v) {
    edge[++tot].u = u;
    edge[tot].v = v;
    edge[tot].next = head[u];
    head[u] = tot;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++index;
    stack[++top] = u;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
        } else if (!belong[v]) {
            low[u] = (low[u] < dfn[v]) ? low[u] : dfn[v];
        }
    }
    if (dfn[u] == low[u]) {
        int v;
        cnt++;
        do {
            v = stack[top--];
            belong[v] = cnt;
        } while (u != v);
    }
}

void init(int u) {
    parent[u] = u;
    size[u] = 1;
}

int find(int u) {
    if (parent[u] == u) return u;
    return parent[u] = find(parent[u]);
}

void union_sets(int u, int v) {
    int root_u = find(u);
    int root_v = find(v);
    if (root_u != root_v) {
        if (size[root_u] > size[root_v]) {
            parent[root_v] = root_u;
            size[root_u] += size[root_v];
        } else {
            parent[root_u] = root_v;
            size[root_v] += size[root_u];
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }

    for (int i = 1; i <= tot; i++) {
        int u = edge[i].u;
        int v = edge[i].v;
        if (belong[u] != belong[v]) {
            union_sets(belong[u], belong[v]);
            in[belong[v]]++;
            out[belong[u]]++;
        }
    }

    for (int i = 1; i <= cnt; i++) {
        if (in[i] == 0) init(i);
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        int op, u, v;
        scanf("%d %d %d", &op, &u, &v);
        if (op == 1) {
            printf("%d\n", ans[find(belong[u])]);
        } else if (op == 0) {
            if (belong[u] != belong[v]) {
                int root_u = find(belong[u]);
                int root_v = find(belong[v]);
                ans[root_u] += size[root_v];
                ans[root_v] += size[root_u];
                union_sets(belong[u], belong[v]);
            }
        }
    }

    return 0;
}