#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define MAXN 200
#define MAXM 10000

typedef struct {
    int x, y;
} Point;

typedef struct {
    int p, q;
    double dist;
} Edge;

Point points[MAXN + 1];
Edge edges[MAXM];
double dist[MAXN + 1][MAXN + 1];
int n, m;

double calculateDistance(int i, int j) {
    return sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x) + 
                (points[i].y - points[j].y) * (points[i].y - points[j].y));
}

void dijkstra(int start) {
    double d[MAXN + 1];
    int visited[MAXN + 1];
    for (int i = 1; i <= n; i++) {
        d[i] = dist[start][i];
        visited[i] = 0;
    }
    d[start] = 0;
    visited[start] = 1;

    for (int i = 1; i < n; i++) {
        int u = -1;
        double minDist = INT_MAX;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && d[j] < minDist) {
                minDist = d[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (!visited[v] && dist[u][v] != INT_MAX && d[u] + dist[u][v] < d[v]) {
                d[v] = d[u] + dist[u][v];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        dist[start][i] = d[i];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i].p, &edges[i].q);
        edges[i].dist = calculateDistance(edges[i].p, edges[i].q);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    for (int i = 0; i < m; i++) {
        dist[edges[i].p][edges[i].q] = edges[i].dist;
        dist[edges[i].q][edges[i].p] = edges[i].dist;
    }

    dijkstra(1);

    double shortestPath = dist[1][n];
    double secondShortestPath = INT_MAX;

    for (int i = 0; i < m; i++) {
        int p = edges[i].p;
        int q = edges[i].q;
        double detour = dist[1][p] + dist[q][n] + edges[i].dist;
        if (detour > shortestPath && detour < secondShortestPath) {
            secondShortestPath = detour;
        }
        detour = dist[1][q] + dist[p][n] + edges[i].dist;
        if (detour > shortestPath && detour < secondShortestPath) {
            secondShortestPath = detour;
        }
    }

    if (secondShortestPath == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%.2f\n", secondShortestPath);
    }

    return 0;
}