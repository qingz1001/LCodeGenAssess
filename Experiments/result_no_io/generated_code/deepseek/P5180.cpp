#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 200005
#define MAXM 300005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], edge_count;
int dfn[MAXN], low[MAXN], dfstime;
int stack[MAXN], top;
bool in_stack[MAXN];
int scc_id[MAXN], scc_size[MAXN], scc_count;
int in_degree[MAXN];
int dp[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++dfstime;
    stack[++top] = u;
    in_stack[u] = true;

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
        ++scc_count;
        int v;
        do {
            v = stack[top--];
            in_stack[v] = false;
            scc_id[v] = scc_count;
            scc_size[scc_count]++;
        } while (v != u);
    }
}

void topological_sort(int n) {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= scc_count; ++i) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
            dp[i] = scc_size[i];
        }
    }

    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            dp[v] += dp[u];
            if (--in_degree[v] == 0) {
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i) {
        head[i] = -1;
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = head[i]; j != -1; j = edges[j].next) {
            int u = scc_id[i], v = scc_id[edges[j].to];
            if (u != v) {
                add_edge(u, v);
                in_degree[v]++;
            }
        }
    }

    topological_sort(n);

    for (int i = 1; i <= n; ++i) {
        printf("%d ", dp[scc_id[i]]);
    }
    printf("\n");

    return 0;
}