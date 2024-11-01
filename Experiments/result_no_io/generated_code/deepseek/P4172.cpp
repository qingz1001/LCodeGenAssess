#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1005
#define MAXM 100005
#define MAXQ 100005

typedef struct {
    int u, v, t;
} Edge;

typedef struct {
    int k, u, v;
} Task;

Edge edges[MAXM];
Task tasks[MAXQ];
int parent[MAXN];
int rank[MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_set(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->t - ((Edge *)b)->t;
}

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].t);
    }

    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &tasks[i].k, &tasks[i].u, &tasks[i].v);
    }

    qsort(edges, m, sizeof(Edge), compare);

    for (int i = 0; i < q; i++) {
        if (tasks[i].k == 1) {
            int u = tasks[i].u;
            int v = tasks[i].v;
            int max_time = INT_MIN;
            for (int j = 0; j < m; j++) {
                if (find(edges[j].u) != find(edges[j].v)) {
                    union_set(edges[j].u, edges[j].v);
                }
                if (find(u) == find(v)) {
                    max_time = edges[j].t;
                    break;
                }
            }
            printf("%d\n", max_time);
        } else if (tasks[i].k == 2) {
            int u = tasks[i].u;
            int v = tasks[i].v;
            for (int j = 0; j < m; j++) {
                if ((edges[j].u == u && edges[j].v == v) || (edges[j].u == v && edges[j].v == u)) {
                    edges[j].t = INT_MAX;
                    break;
                }
            }
        }
    }

    return 0;
}