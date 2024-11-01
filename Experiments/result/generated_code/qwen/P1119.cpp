#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 205
#define MAXM 20005
#define MAXQ 50005

typedef struct {
    int to, weight;
} Edge;

int n, m, q;
int t[MAXN];
Edge edges[MAXM];
int dist[MAXN][MAXN];

void dijkstra(int start) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INT_MAX / 2;
        }
    }
    dist[start][start] = 0;
    for (int k = 0; k < n; k++) {
        if (dist[start][k] == INT_MAX / 2) continue;
        for (int e = 0; e < m; e++) {
            if (edges[e].to == k || edges[e].to == start) {
                int v = edges[e].to == k ? start : edges[e].to;
                int u = edges[e].to == k ? edges[e].to : start;
                dist[v][u] = dist[u][v] = fmin(dist[u][v], dist[v][k] + edges[e].weight);
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);
        if (t < t[x] || t < t[y]) {
            printf("-1\n");
        } else {
            if (dist[x][y] == INT_MAX / 2) {
                printf("-1\n");
            } else {
                printf("%d\n", dist[x][y]);
            }
        }
    }
    return 0;
}