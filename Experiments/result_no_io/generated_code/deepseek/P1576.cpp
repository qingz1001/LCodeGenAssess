#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2005
#define INF 1e9

typedef struct {
    int to;
    double rate;
} Edge;

Edge graph[MAXN][MAXN];
double dist[MAXN];
int n, m;

void dijkstra(int start) {
    int i, j, min_index;
    double min_dist;
    int visited[MAXN] = {0};

    for (i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[start] = 100.0;

    for (i = 1; i <= n; i++) {
        min_dist = INF;
        min_index = -1;
        for (j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                min_index = j;
            }
        }
        if (min_index == -1) break;
        visited[min_index] = 1;

        for (j = 1; j <= n; j++) {
            if (graph[min_index][j].rate > 0 && !visited[j]) {
                double new_dist = dist[min_index] / (1 - graph[min_index][j].rate / 100.0);
                if (new_dist < dist[j]) {
                    dist[j] = new_dist;
                }
            }
        }
    }
}

int main() {
    int i, x, y, z, A, B;

    scanf("%d %d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &z);
        graph[x][y].rate = z;
        graph[y][x].rate = z;
    }
    scanf("%d %d", &A, &B);

    dijkstra(B);

    printf("%.8f\n", dist[A]);

    return 0;
}