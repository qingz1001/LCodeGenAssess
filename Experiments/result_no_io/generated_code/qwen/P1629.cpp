#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 100005

typedef struct {
    int v, w;
} Edge;

int n, m;
Edge edges[MAXM];
int dist[MAXN][MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = 1e9;
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != 1e9 && dist[k][j] != 1e9) {
                    dist[i][j] = dist[i][j] > dist[i][k] + dist[k][j] ? dist[i][k] + dist[k][j] : dist[i][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    dijkstra(1);

    int min_time = 1e9;
    for (int i = 2; i <= n; i++) {
        min_time = min_time > dist[1][i] * 2 + dist[i][1] ? dist[1][i] * 2 + dist[i][1] : min_time;
    }

    printf("%d\n", min_time);

    return 0;
}