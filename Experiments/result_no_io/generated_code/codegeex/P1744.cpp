#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100
#define MAXM 1000
#define INF 1e9

typedef struct {
    int x, y;
} Point;

typedef struct {
    int u, v;
} Edge;

int n, m, s, t;
Point points[MAXN];
Edge edges[MAXM];
double dist[MAXN][MAXN];

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
    }

    scanf("%d %d", &s, &t);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        dist[u][v] = sqrt((points[u].x - points[v].x) * (points[u].x - points[v].x) + (points[u].y - points[v].y) * (points[u].y - points[v].y));
        dist[v][u] = dist[u][v];
    }

    floyd();

    if (dist[s][t] == INF) {
        printf("No path found\n");
    } else {
        printf("%.2lf\n", dist[s][t]);
    }

    return 0;
}