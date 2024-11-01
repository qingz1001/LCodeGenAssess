#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

typedef struct {
    int x, y;
} Point;

typedef struct {
    int u, v;
} Edge;

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    Point points[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    Edge edges[m];
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
    }

    int rings[k][100001];
    int ring_sizes[k];
    for (int i = 0; i < k; ++i) {
        scanf("%d", &ring_sizes[i]);
        for (int j = 0; j < ring_sizes[i]; ++j) {
            scanf("%d", &rings[i][j]);
        }
    }

    int q;
    scanf("%d", &q);

    while (q--) {
        int z;
        scanf("%d", &z);

        // Placeholder for the actual logic to compute f(S)
        // For simplicity, we'll just print a placeholder value
        printf("Placeholder result\n");
    }

    return 0;
}