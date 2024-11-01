#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 600000
#define MAXM 1200000

int n, m, q;
int tot, head[MAXN], to[MAXM], nxt[MAXM], val[MAXM];
int dfn[MAXN], low[MAXN], idx, st[MAXN], top, belong[MAXN], cnt;
int in[MAXN], out[MAXN], ans[MAXN], scc_cnt;

void add(int u, int v, int w) {
    to[tot] = v;
    val[tot] = w;
    nxt[tot] = head[u];
    head[u] = tot++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    st[++top] = u;
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
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
            v = st[top--];
            belong[v] = cnt;
        } while (u != v);
    }
}

void dfs(int u, int fa) {
    in[u] = 0;
    out[u] = 0;
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        if (belong[u] != belong[v]) {
            in[u] += in[v];
            out[u] += out[v];
        }
    }
    if (val[u] == 1) {
        in[u]++;
    } else {
        out[u]++;
    }
    if (in[u] > 0 && out[u] > 0) {
        ans[u] = 1;
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    dfs(1, 0);
    scanf("%d", &q);
    while (q--) {
        int s, t;
        scanf("%d%d", &s, &t);
        if (belong[s] == belong[t] && ans[belong[s]]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}