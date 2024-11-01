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
int visited[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int u, int *total_w, int *total_c) {
    visited[u] = 1;
    *total_w += factories[u].w;
    *total_c += factories[u].c;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!visited[v]) {
            dfs(v, total_w, total_c);
        }
    }
}

double max_ratio(int N, int M) {
    double max_r = -DBL_MAX;
    for (int i = 0; i < (1 << N); i++) {
        if (__builtin_popcount(i) == N - M) {
            int total_w = 0, total_c = 0;
            for (int j = 0; j < N; j++) {
                visited[j] = 0;
            }
            for (int j = 0; j < N; j++) {
                if (!(i & (1 << j))) {
                    dfs(j, &total_w, &total_c);
                    break;
                }
            }
            for (int j = 0; j < N; j++) {
                if (!visited[j] && !(i & (1 << j))) {
                    total_w = 0;
                    total_c = 0;
                    break;
                }
            }
            if (total_c != 0) {
                double r = (double)total_w / total_c;
                if (r > max_r) {
                    max_r = r;
                }
            }
        }
    }
    return max_r;
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
    for (int i = 0; i < N; i++) {
        head[i] = -1;
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a - 1, b - 1);
        add_edge(b - 1, a - 1);
    }
    double result = max_ratio(N, M);
    printf("%.1f\n", result);
    return 0;
}