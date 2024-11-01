#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 500005

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], cnt;
int dfn[MAXN], low[MAXN], stack[MAXN], instack[MAXN];
int scc[MAXN], scc_cnt, top, tim;
int in[MAXN];

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    stack[++top] = u;
    instack[u] = 1;
    
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (instack[v] && dfn[v] < low[u]) {
            low[u] = dfn[v];
        }
    }
    
    if (dfn[u] == low[u]) {
        scc_cnt++;
        int v;
        do {
            v = stack[top--];
            instack[v] = 0;
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
    }
    
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (scc[u] != scc[v]) {
                in[scc[v]]++;
            }
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (in[i] == 0) ans++;
    }
    
    printf("%d\n", ans);
    
    return 0;
}