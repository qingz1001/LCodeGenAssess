#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5005
#define MAXM 50005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
int low[MAXN], dfn[MAXN], stack[MAXN], top = 0;
int scc[MAXN], scc_count = 0, time_stamp = 0;
int in_stack[MAXN], scc_size[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void tarjan(int u) {
    low[u] = dfn[u] = ++time_stamp;
    stack[top++] = u;
    in_stack[u] = 1;

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!dfn[v]) {
            tarjan(v);
            if (low[u] > low[v]) low[u] = low[v];
        } else if (in_stack[v] && low[u] > dfn[v]) {
            low[u] = dfn[v];
        }
    }

    if (low[u] == dfn[u]) {
        ++scc_count;
        int v;
        do {
            v = stack[--top];
            in_stack[v] = 0;
            scc[v] = scc_count;
            scc_size[scc_count]++;
        } while (v != u);
    }
}

int compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
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

    int max_scc_size = 0, max_scc_index = 0;
    for (int i = 1; i <= scc_count; ++i) {
        if (scc_size[i] > max_scc_size) {
            max_scc_size = scc_size[i];
            max_scc_index = i;
        }
    }

    int result[MAXN], result_count = 0;
    for (int i = 1; i <= N; ++i) {
        if (scc[i] == max_scc_index) {
            result[result_count++] = i;
        }
    }

    qsort(result, result_count, sizeof(int), compare);

    printf("%d\n", max_scc_size);
    for (int i = 0; i < result_count; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}