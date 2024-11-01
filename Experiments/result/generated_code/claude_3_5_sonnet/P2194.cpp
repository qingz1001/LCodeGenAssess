#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 300005
#define MOD 1000000007

int n, m;
long long w[MAXN];
int head[MAXN], to[MAXM], nxt[MAXM], tot;
int dfn[MAXN], low[MAXN], stk[MAXN], top, scc[MAXN], scc_cnt, timer;
long long scc_min[MAXN], scc_sum[MAXN], scc_cnt_min[MAXN];
int vis[MAXN];

void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    stk[++top] = u;
    vis[u] = 1;
    
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (vis[v] && dfn[v] < low[u]) {
            low[u] = dfn[v];
        }
    }
    
    if (dfn[u] == low[u]) {
        int v;
        scc_cnt++;
        do {
            v = stk[top--];
            scc[v] = scc_cnt;
            vis[v] = 0;
            if (w[v] < scc_min[scc_cnt] || scc_min[scc_cnt] == 0) {
                scc_min[scc_cnt] = w[v];
                scc_cnt_min[scc_cnt] = 1;
            } else if (w[v] == scc_min[scc_cnt]) {
                scc_cnt_min[scc_cnt]++;
            }
            scc_sum[scc_cnt] += w[v];
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
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    
    long long min_cost = 0;
    long long ways = 1;
    
    for (int i = 1; i <= scc_cnt; i++) {
        min_cost += scc_min[i];
        ways = (ways * scc_cnt_min[i]) % MOD;
    }
    
    printf("%lld %lld\n", min_cost, ways);
    
    return 0;
}