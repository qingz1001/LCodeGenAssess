#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define MAXM 120
#define INF 1000000

typedef struct {
    int i, j, k;
} Edge;

int n, m;
Edge edges[MAXM];
int dist[MAXN];
int prev[MAXN];

void bellman_ford() {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[1] = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = edges[j].i;
            int v = edges[j].j;
            int w = edges[j].k;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
            }
        }
    }
}

void print_path(int v) {
    if (v == -1) return;
    print_path(prev[v]);
    printf("%d ", v);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].i, &edges[i].j, &edges[i].k);
    }

    bellman_ford();

    printf("%d\n", dist[n]);
    print_path(n);
    printf("\n");

    return 0;
}