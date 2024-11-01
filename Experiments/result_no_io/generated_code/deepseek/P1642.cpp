#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAXN 100

typedef struct {
    int w; // 产值
    int c; // 污染值
} Factory;

typedef struct {
    int to;
    int next;
} Edge;

Factory factories[MAXN];
Edge edges[2 * MAXN];
int head[MAXN], edge_count = 0;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

double max_ratio = -DBL_MAX;

void dfs(int node, int parent, int N, int M, int sum_w, int sum_c) {
    sum_w += factories[node].w;
    sum_c += factories[node].c;

    if (N - M == 1) {
        double ratio = (double)sum_w / sum_c;
        if (ratio > max_ratio) {
            max_ratio = ratio;
        }
        return;
    }

    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to != parent) {
            dfs(to, node, N, M - 1, sum_w, sum_c);
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        scanf("%d", &factories[i].w);
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &factories[i].c);
    }

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a - 1, b - 1);
        add_edge(b - 1, a - 1);
    }

    for (int i = 0; i < N; i++) {
        dfs(i, -1, N, M, 0, 0);
    }

    printf("%.1f\n", max_ratio);

    return 0;
}