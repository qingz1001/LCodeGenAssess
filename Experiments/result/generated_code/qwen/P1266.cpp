#include <stdio.h>
#include <stdlib.h>

#define MAX_N 150
#define INF 1000000000

typedef struct {
    int from, to, speed, length;
} Road;

int min(int a, int b) {
    return (a < b) ? a : b;
}

void dijkstra(int n, int m, int d, Road roads[], int *dist, int *path) {
    int visited[MAX_N] = {0};
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        path[i] = -1;
    }
    dist[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        visited[u] = 1;
        for (int i = 0; i < m; i++) {
            if (roads[i].from == u) {
                int v = roads[i].to;
                int speed = roads[i].speed;
                int length = roads[i].length;
                int time = (speed > 0) ? length / speed : length / 70;

                if (!visited[v] && dist[u] + time < dist[v]) {
                    dist[v] = dist[u] + time;
                    path[v] = u;
                }
            }
        }
    }
}

int main() {
    int n, m, d;
    scanf("%d %d %d", &n, &m, &d);

    Road roads[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &roads[i].from, &roads[i].to, &roads[i].speed, &roads[i].length);
    }

    int dist[MAX_N], path[MAX_N];
    dijkstra(n, m, d, roads, dist, path);

    if (dist[d] == INF) {
        printf("-1\n");
        return 0;
    }

    int current = d;
    while (current != -1) {
        printf("%d ", current);
        current = path[current];
    }
    printf("\n");

    return 0;
}