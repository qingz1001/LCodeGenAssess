#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 500005

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], cnt;
int dfn[MAXN], low[MAXN], stack[MAXN], instack[MAXN];
int scc[MAXN], scc_cnt, top, dfn_cnt;
int in_degree[MAXN];

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++dfn_cnt;
    stack[++top] = u;
    instack[u] = 1;

    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = low[u] < low[v] ? low[u] : low[v];
        } else if (instack[v]) {
            low[u] = low[u] < dfn[v] ? low[u] : dfn[v];
        }
    }

    if (dfn[u] == low[u]) {
        int v;
        scc_cnt++;
        do {
            v = stack[top--];
            instack[v] = 0;
            scc[v] = scc_cnt;
        } while (v != u);
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (scc[u] != scc[v]) {
                in_degree[scc[v]]++;
            }
        }
    }

    int result = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (in_degree[i] == 0) {
            result++;
        }
    }

    printf("%d\n", result);

    return 0;
}