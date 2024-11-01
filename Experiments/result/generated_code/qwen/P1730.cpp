#include <stdio.h>
#include <stdlib.h>

#define INF 1e9
#define EPS 1e-9

typedef struct {
    int to, weight;
} Edge;

int n, m, q;
Edge edges[1005];
int dist[55][55];
double density[55][55];

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    density[i][j] = (density[i][k] * (dist[i][k] + dist[k][j] - dist[i][k]) + density[k][j] * (dist[k][j] - dist[i][k])) / (dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
        dist[edges[i].from][edges[i].to] = edges[i].weight;
        density[edges[i].from][edges[i].to] = (double)edges[i].weight / 1.0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist[i][j] = 0;
                density[i][j] = 0;
            } else if (!dist[i][j]) {
                dist[i][j] = INF;
                density[i][j] = INF;
            }
        }
    }
    floyd();
    scanf("%d", &q);
    while (q--) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (density[x][y] >= INF - EPS) {
            printf("OMG!\n");
        } else {
            printf("%.3f\n", density[x][y]);
        }
    }
    return 0;
}