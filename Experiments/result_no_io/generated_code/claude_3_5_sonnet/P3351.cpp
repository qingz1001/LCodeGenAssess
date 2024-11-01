#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

int n, m;
int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], tot;
int dfn[MAXN], low[MAXN], stk[MAXN], top, idx;
int scc[MAXN], scc_cnt;
int in_stk[MAXN];
int degree[MAXN];

void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    stk[++top] = u;
    in_stk[u] = 1;
    
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (in_stk[v] && dfn[v] < low[u]) {
            low[u] = dfn[v];
        }
    }
    
    if (dfn[u] == low[u]) {
        int v;
        scc_cnt++;
        do {
            v = stk[top--];
            in_stk[v] = 0;
            scc[v] = scc_cnt;
        } while (v != u);
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
    
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (scc[u] != scc[v]) {
                degree[scc[u]]++;
            }
        }
    }
    
    long long ans = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (degree[i] == 1) ans++;
    }
    ans = ans * (ans - 1) / 2;
    
    for (int i = 1; i <= scc_cnt; i++) {
        int cnt = 0;
        for (int u = 1; u <= n; u++) {
            if (scc[u] == i) cnt++;
        }
        ans += (long long)cnt * (cnt - 1) / 2;
    }
    
    printf("%lld\n", ans);
    
    return 0;
}