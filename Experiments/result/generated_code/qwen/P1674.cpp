#include <stdio.h>
#include <stdlib.h>

#define MAX_N 205
#define MAX_P 40005
#define INF 1e9

typedef struct {
    int a, b, l;
} Edge;

int n, p, t;
Edge edges[MAX_P];
int dist[MAX_N][MAX_N];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }

    for (int i = 0; i < p; i++) {
        dist[edges[i].a][edges[i].b] = edges[i].l;
        dist[edges[i].b][edges[i].a] = edges[i].l;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = fmin(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &p, &t);
    for (int i = 0; i < p; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].l);
    }

    int result = INF;
    for (int i = 0; i < p; i++) {
        for (int j = i + 1; j < p; j++) {
            int max_length = -1;
            dijkstra(edges[i].a);
            for (int k = 1; k <= n; k++) {
                if (dist[k][edges[j].b] != INF) {
                    max_length = fmax(max_length, dist[k][edges[j].b]);
                }
            }
            result = fmin(result, max_length);
        }
    }

    printf("%d\n", result);
    return 0;
}