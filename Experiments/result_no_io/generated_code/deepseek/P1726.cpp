#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5005
#define MAXM 50005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_cnt = 0;
int dfn[MAXN], low[MAXN], stack[MAXN], top = 0;
int scc[MAXN], scc_cnt = 0, time_stamp = 0;
int in_stack[MAXN];
int scc_size[MAXN];

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++time_stamp;
    stack[top++] = u;
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
        ++scc_cnt;
        int v;
        do {
            v = stack[--top];
            in_stack[v] = 0;
            scc[v] = scc_cnt;
            scc_size[scc_cnt]++;
        } while (v != u);
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    memset(head, -1, sizeof(head));

    for (int i = 0; i < M; ++i) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        if (t == 1) {
            add_edge(a, b);
        } else {
            add_edge(a, b);
            add_edge(b, a);
        }
    }

    for (int i = 1; i <= N; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    int max_scc_size = 0, max_scc_id = 0;
    for (int i = 1; i <= scc_cnt; ++i) {
        if (scc_size[i] > max_scc_size) {
            max_scc_size = scc_size[i];
            max_scc_id = i;
        }
    }

    printf("%d\n", max_scc_size);
    for (int i = 1; i <= N; ++i) {
        if (scc[i] == max_scc_id) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}