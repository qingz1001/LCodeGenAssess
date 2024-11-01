#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define MAXM 1000005

int n, m, q;
int head[MAXN], to[MAXM], nxt[MAXM], cnt;
int dfn[MAXN], low[MAXN], timer;
int stack[MAXN], top;
int scc[MAXN], scc_cnt;
int in_stack[MAXN];

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    stack[++top] = u;
    in_stack[u] = 1;

    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (in_stack[v] && dfn[v] < low[u]) {
            low[u] = dfn[v];
        }
    }

    if (dfn[u] == low[u]) {
        scc_cnt++;
        int v;
        do {
            v = stack[top--];
            in_stack[v] = 0;
            scc[v] = scc_cnt;
        } while (v != u);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }

    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (scc[u] == scc[v]) {
            printf("%d\n", 2);
        } else {
            printf("%d\n", 3);
        }
    }

    return 0;
}