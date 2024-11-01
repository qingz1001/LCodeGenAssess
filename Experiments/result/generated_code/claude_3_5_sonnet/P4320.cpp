#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define MAXM 1000005

int n, m, q;
int head[MAXN], to[MAXM], next[MAXM], tot;
int dfn[MAXN], low[MAXN], timestamp;
int stk[MAXN], top;
int scc[MAXN], scc_cnt;
int scc_size[MAXN];
int is_cut[MAXN];

void add_edge(int u, int v) {
    to[++tot] = v;
    next[tot] = head[u];
    head[u] = tot;
}

void tarjan(int u, int fa) {
    int child = 0;
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;

    for (int i = head[u]; i; i = next[i]) {
        int v = to[i];
        if (!dfn[v]) {
            child++;
            tarjan(v, u);
            low[u] = low[u] < low[v] ? low[u] : low[v];
            if (low[v] >= dfn[u] && u != fa) {
                is_cut[u] = 1;
            }
        } else if (v != fa) {
            low[u] = low[u] < dfn[v] ? low[u] : dfn[v];
        }
    }

    if (u == fa && child > 1) {
        is_cut[u] = 1;
    }

    if (low[u] == dfn[u]) {
        scc_cnt++;
        int v;
        do {
            v = stk[top--];
            scc[v] = scc_cnt;
            scc_size[scc_cnt]++;
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
        if (!dfn[i]) {
            tarjan(i, i);
        }
    }

    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (scc[u] == scc[v]) {
            printf("%d\n", scc_size[scc[u]]);
        } else {
            int ans = 2;
            if (is_cut[u]) ans++;
            if (is_cut[v]) ans++;
            printf("%d\n", ans);
        }
    }

    return 0;
}