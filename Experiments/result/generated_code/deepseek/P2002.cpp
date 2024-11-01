#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXN * 5];
int head[MAXN];
int low[MAXN], dfn[MAXN], stack[MAXN], belong[MAXN];
bool in_stack[MAXN];
int idx, top, scc_cnt;

void add_edge(int u, int v, int id) {
    edges[id].to = v;
    edges[id].next = head[u];
    head[u] = id;
}

void tarjan(int u) {
    low[u] = dfn[u] = ++idx;
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

    if (low[u] == dfn[u]) {
        scc_cnt++;
        int v;
        do {
            v = stack[top--];
            in_stack[v] = false;
            belong[v] = scc_cnt;
        } while (v != u);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        dfn[i] = 0;
        in_stack[i] = false;
    }

    for (int i = 0; i < m; i++) {
        int b, e;
        scanf("%d %d", &b, &e);
        add_edge(b, e, i);
    }

    idx = top = scc_cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    int *in_degree = (int *)calloc(scc_cnt + 1, sizeof(int));
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            if (belong[u] != belong[v]) {
                in_degree[belong[v]]++;
            }
        }
    }

    int result = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (in_degree[i] == 0) {
            result++;
        }
    }

    printf("%d\n", result);

    free(in_degree);
    return 0;
}