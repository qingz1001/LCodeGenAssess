#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 300005
#define MOD 1000000007

typedef struct {
    int v;
    int next;
} Edge;

Edge edges[MAXM];
int head[MAXN], cnt;
int n, m;
int gas[MAXN];
int min_cost = 0;
long long ways = 1;

void add_edge(int u, int v) {
    edges[cnt].v = v;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

int visited[MAXN];
int in_degree[MAXN];
int low[MAXN];
int disc[MAXN];
int stack[MAXN];
int parent[MAXN];
int scc_count = 0;
int scc[MAXN];
int scc_min_gas[MAXN];
int scc_size[MAXN];
int stack_top = 0;
int time = 0;

void dfs(int u) {
    visited[u] = 1;
    disc[u] = low[u] = ++time;
    stack[stack_top++] = u;
    parent[u] = -1;

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        if (!visited[v]) {
            dfs(v);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
        } else if (parent[u] != v) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }

    if (low[u] == disc[u]) {
        scc_count++;
        int v;
        do {
            v = stack[--stack_top];
            scc[v] = scc_count;
            scc_min_gas[scc_count] = (scc_min_gas[scc_count] < gas[v]) ? scc_min_gas[scc_count] : gas[v];
            scc_size[scc_count]++;
            parent[v] = -1;
        } while (v != u);
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &gas[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        add_edge(u, v);
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    for (int i = 1; i <= scc_count; i++) {
        min_cost += scc_min_gas[i];
        ways = (ways * scc_size[i]) % MOD;
    }

    printf("%d %lld\n", min_cost, ways);
    return 0;
}