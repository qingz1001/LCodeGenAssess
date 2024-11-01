#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2000
#define MAXM 100000

typedef struct {
    int to;
    double rate;
} Edge;

Edge graph[MAXN][MAXN];
double dist[MAXN];
int n, m;

void dijkstra(int start) {
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 100.0;

    int visited[MAXN] = {0};
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        visited[u] = 1;
        for (int j = 0; j < n; j++) {
            if (graph[u][j].to != -1) {
                double new_dist = dist[u] / (1 - graph[u][j].rate / 100.0);
                if (new_dist < dist[j]) {
                    dist[j] = new_dist;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j].to = -1;
        }
    }
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        x--; y--;
        graph[x][y].to = y;
        graph[x][y].rate = z;
        graph[y][x].to = x;
        graph[y][x].rate = z;
    }
    int A, B;
    scanf("%d %d", &A, &B);
    A--; B--;

    dijkstra(A);

    printf("%.8f\n", dist[B]);

    return 0;
}