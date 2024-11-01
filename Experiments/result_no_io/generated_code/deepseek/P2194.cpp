#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 100005
#define MAXM 300005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], edge_count;
int w[MAXN], dfn[MAXN], low[MAXN], stack[MAXN], top, time_stamp;
int scc_id[MAXN], scc_min_cost[MAXN], scc_count[MAXN], scc_index;
int in_stack[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++time_stamp;
    stack[++top] = u;
    in_stack[u] = 1;

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!dfn[v]) {
            tarjan(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (in_stack[v] && dfn[v] < low[u]) {
            low[u] = dfn[v];
        }
    }

    if (dfn[u] == low[u]) {
        ++scc_index;
        int v;
        do {
            v = stack[top--];
            in_stack[v] = 0;
            scc_id[v] = scc_index;
            if (w[v] < scc_min_cost[scc_index]) {
                scc_min_cost[scc_index] = w[v];
                scc_count[scc_index] = 1;
            } else if (w[v] == scc_min_cost[scc_index]) {
                scc_count[scc_index]++;
            }
        } while (u != v);
    }
}

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &w[i]);
    }
    scanf("%d", &m);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    memset(scc_min_cost, 0x3f, sizeof(scc_min_cost));
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    long long total_cost = 0, total_count = 1;
    for (int i = 1; i <= scc_index; ++i) {
        total_cost += scc_min_cost[i];
        total_count = (total_count * scc_count[i]) % MOD;
    }

    printf("%lld %lld\n", total_cost, total_count);
    return 0;
}