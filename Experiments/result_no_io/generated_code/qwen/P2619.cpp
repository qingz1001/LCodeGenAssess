#include <stdio.h>
#include <stdlib.h>

#define MAXN 50010
#define INF 0x3f3f3f3f

typedef struct {
    int u, v, w, c;
} Edge;

int n, m, need;
Edge edges[MAXN];
int parent[MAXN];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
    parent[find(x)] = find(y);
}

int kruskal() {
    for (int i = 0; i <= n; i++) parent[i] = i;
    qsort(edges, m, sizeof(Edge), [](const void *a, const void *b) {
        return ((Edge *)a)->w - ((Edge *)b)->w;
    });

    int count = 0, white_count = 0, sum = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w, c = edges[i].c;
        if (find(u) == find(v)) continue;
        if (c == 0 && white_count < need) {
            union_sets(u, v);
            sum += w;
            white_count++;
            count++;
        } else if (c == 1) {
            union_sets(u, v);
            sum += w;
            count++;
        }
        if (count == n - 1) break;
    }

    if (white_count != need) return -1;
    return sum;
}

int main() {
    scanf("%d %d %d", &n, &m, &need);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].w, &edges[i].c);
    }

    int result = kruskal();
    printf("%d\n", result);

    return 0;
}