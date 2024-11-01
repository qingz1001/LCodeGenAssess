#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1005
#define MAX_P 10005
#define INF 0x3f3f3f3f

typedef struct {
    int a, b, l;
} Edge;

int n, p, k;
Edge edges[MAX_P];
int parent[MAX_N];

int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void union_set(int x, int y) {
    parent[find(x)] = find(y);
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->l - ((Edge *)b)->l;
}

int main() {
    scanf("%d %d %d", &n, &p, &k);
    for (int i = 0; i < p; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].l);
    }

    qsort(edges, p, sizeof(Edge), compare);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    int min_cost = 0;
    int used_edges = 0;
    int free_edges = 0;

    for (int i = 0; i < p; i++) {
        int u = edges[i].a, v = edges[i].b, w = edges[i].l;
        int pu = find(u), pv = find(v);

        if (pu != pv) {
            union_set(pu, pv);
            used_edges++;
            if (free_edges < k) {
                free_edges++;
            } else {
                min_cost = w;
            }
        }
    }

    if (used_edges + free_edges < n - 1) {
        printf("-1\n");
    } else {
        printf("%d\n", min_cost);
    }

    return 0;
}