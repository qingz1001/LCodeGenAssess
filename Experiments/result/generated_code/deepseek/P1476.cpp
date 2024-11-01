#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXM 120

typedef struct {
    int from, to, time;
} Edge;

int n, m;
Edge edges[MAXM];
int dist[MAXN + 1];
int prev[MAXN + 1];

void bellman_ford() {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[1] = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = edges[j].from;
            int v = edges[j].to;
            int w = edges[j].time;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
            }
        }
    }
}

void print_path(int v) {
    if (prev[v] != -1) {
        print_path(prev[v]);
    }
    printf("%d ", v);
}

int main() {
    scanf("%d", &n);
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].time);
    }

    bellman_ford();

    printf("%d\n", dist[n]);
    print_path(n);
    printf("\n");

    return 0;
}