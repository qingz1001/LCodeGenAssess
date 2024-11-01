#include <stdio.h>
#include <stdlib.h>

#define MAXN 3005
#define MAXM 20005

typedef struct {
    int to, weight;
} Edge;

Edge edges[MAXM];
int degree[MAXN];
int parent[MAXN];

void add_edge(int u, int v, int w) {
    edges[degree[u]].to = v;
    edges[degree[u]].weight = w;
    degree[u]++;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    parent[find(x)] = find(y);
}

int main() {
    int n, m, s, t, k;
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &k);

    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    int result[MAXM];
    int count = 0;

    for (int i = 0; i < m; i++) {
        int u = edges[i].to;
        int v = edges[i].from;
        int w = edges[i].weight;

        int pu = find(u);
        int pv = find(v);

        if (pu != pv) {
            union_sets(pu, pv);
            if (pu == s || pv == s) {
                result[count++] = w;
            }
        }
    }

    qsort(result, count, sizeof(int), (int (*)(const void *, const void *))strcmp);

    if (count < k) {
        printf("%d\n", count);
        for (int i = 0; i < count; i++) {
            printf("%d\n", result[i]);
        }
        printf("-1\n");
    } else {
        for (int i = 0; i < k; i++) {
            printf("%d\n", result[i]);
        }
    }

    return 0;
}