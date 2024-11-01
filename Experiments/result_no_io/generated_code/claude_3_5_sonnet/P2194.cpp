#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 300005
#define MOD 1000000007

int n, m;
long long w[MAX_N];
int head[MAX_N], to[MAX_M], nxt[MAX_M], tot;
int dfn[MAX_N], low[MAX_N], stk[MAX_N], top, cnt;
int scc[MAX_N], scc_cnt;
long long scc_w[MAX_N];
int scc_size[MAX_N];
int in_stk[MAX_N];

void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
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
        scc_cnt++;
        int v;
        do {
            v = stk[top--];
            in_stk[v] = 0;
            scc[v] = scc_cnt;
            scc_w[scc_cnt] = (scc_w[scc_cnt] < w[v]) ? w[v] : scc_w[scc_cnt];
            scc_size[scc_cnt]++;
        } while (v != u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &w[i]);
    }
    
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    
    long long min_cost = 0;
    long long ways = 1;
    
    for (int i = 1; i <= scc_cnt; i++) {
        min_cost += scc_w[i];
        if (scc_size[i] > 1) {
            ways = (ways * scc_size[i]) % MOD;
        }
    }
    
    printf("%lld %lld\n", min_cost, ways);
    
    return 0;
}