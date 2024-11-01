#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define INF 0x3f3f3f3f

int n, m, p;
int T[MAX_N];
int next[MAX_N], pre[MAX_N];
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], tot;
int stk[MAX_N], top;
int dfn[MAX_N], low[MAX_N], scc[MAX_N], scc_cnt, idx;
int f[MAX_N], g[MAX_N], h[MAX_N];

void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    stk[++top] = u;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (!scc[v] && dfn[v] < low[u]) {
            low[u] = dfn[v];
        }
    }
    if (dfn[u] == low[u]) {
        scc_cnt++;
        while (1) {
            int v = stk[top--];
            scc[v] = scc_cnt;
            if (v == u) break;
        }
    }
}

int solve() {
    memset(head, 0, sizeof(head));
    tot = 0;
    for (int i = 1; i <= n; i++) {
        if (T[i] <= T[next[i]]) {
            add_edge(i, next[i]);
        } else {
            add_edge(next[i], i);
        }
    }
    memset(dfn, 0, sizeof(dfn));
    memset(scc, 0, sizeof(scc));
    scc_cnt = idx = top = 0;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    for (int i = 1; i <= scc_cnt; i++) {
        f[i] = g[i] = -INF;
        h[i] = INF;
    }
    for (int i = 1; i <= n; i++) {
        int s = scc[i];
        if (T[i] > f[s]) f[s] = T[i];
        if (T[i] < h[s]) h[s] = T[i];
        if (T[next[i]] > g[s]) g[s] = T[next[i]];
    }
    int ans = -INF;
    for (int i = 1; i <= scc_cnt; i++) {
        if (f[i] > ans) ans = f[i];
        if (g[i] > ans) ans = g[i];
    }
    return ans;
}

int main() {
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &T[i]);
        next[i] = i % n + 1;
        pre[next[i]] = i;
    }
    int last_ans = solve();
    printf("%d\n", last_ans);
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (p) {
            x ^= last_ans;
            y ^= last_ans;
        }
        T[x] = y;
        last_ans = solve();
        printf("%d\n", last_ans);
    }
    return 0;
}