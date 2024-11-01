#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100
#define INF 1e9

typedef struct {
    int x, y;
} Point;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int n, m;
    Point stores[MAXN + 1];
    int edges[MAXN + 1][MAXN + 1] = {0};
    double dist[MAXN + 1];
    int visited[MAXN + 1] = {0};

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &stores[i].x, &stores[i].y);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        edges[u][v] = edges[v][u] = 1;
    }

    int s, t;
    scanf("%d %d", &s, &t);

    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (edges[u][v] && !visited[v]) {
                double new_dist = dist[u] + distance(stores[u], stores[v]);
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                }
            }
        }
    }

    printf("%.2f\n", dist[t]);

    return 0;
}