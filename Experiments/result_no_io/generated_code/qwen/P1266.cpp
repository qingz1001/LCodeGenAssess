#include <stdio.h>
#include <stdlib.h>

#define MAX_N 150
#define MAX_M 10000
#define INF 1e9

typedef struct {
    int a, b, v, l;
} Road;

int n, m, d;
Road roads[MAX_M];
int dist[MAX_N][MAX_N];
int speed[MAX_N];

void dijkstra(int start) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = (i == j ? 0 : INF);
        }
    }

    for (int i = 0; i < m; i++) {
        if (roads[i].v > 0) {
            dist[roads[i].a][roads[i].b] = roads[i].l / roads[i].v;
        } else {
            dist[roads[i].a][roads[i].b] = roads[i].l / speed[roads[i].a];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = dist[i][j] < dist[i][k] + dist[k][j] ? dist[i][j] : dist[i][k] + dist[k][j];
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &d);
    for (int i = 0; i < n; i++) {
        speed[i] = 70;
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &roads[i].a, &roads[i].b, &roads[i].v, &roads[i].l);
    }

    dijkstra(0);

    printf("%d\n", d);

    return 0;
}