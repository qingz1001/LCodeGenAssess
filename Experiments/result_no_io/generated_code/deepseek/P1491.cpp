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
    double distance;
} Edge;

Point points[MAXN + 1];
Edge edges[MAXM];
double dist[MAXN + 1];
int prev[MAXN + 1];
int visited[MAXN + 1];

double calculateDistance(int i, int j) {
    return sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x) +
                (points[i].y - points[j].y) * (points[i].y - points[j].y));
}

void dijkstra(int n, int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        prev[i] = -1;
    }
    dist[start] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        visited[u] = 1;
        for (int j = 0; j < MAXM; j++) {
            if (edges[j].p == u || edges[j].q == u) {
                int v = edges[j].p == u ? edges[j].q : edges[j].p;
                if (!visited[v] && dist[u] + edges[j].distance < dist[v]) {
                    dist[v] = dist[u] + edges[j].distance;
                    prev[v] = u;
                }
            }
        }
    }
}

double findSecondShortestPath(int n, int start, int end) {
    dijkstra(n, start);
    double firstShortest = dist[end];
    if (firstShortest == INT_MAX) return -1;

    double secondShortest = INT_MAX;
    for (int i = 0; i < MAXM; i++) {
        int u = edges[i].p;
        int v = edges[i].q;
        if (prev[v] == u || prev[u] == v) {
            double originalDistance = edges[i].distance;
            edges[i].distance = INT_MAX;
            dijkstra(n, start);
            edges[i].distance = originalDistance;
            if (dist[end] < secondShortest && dist[end] > firstShortest) {
                secondShortest = dist[end];
            }
        }
    }

    return secondShortest == INT_MAX ? -1 : secondShortest;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    for (int i = 0; i < m; i++) {
        int p, q;
        scanf("%d %d", &p, &q);
        edges[i].p = p;
        edges[i].q = q;
        edges[i].distance = calculateDistance(p, q);
    }

    double result = findSecondShortestPath(n, 1, n);
    if (result == -1) {
        printf("-1\n");
    } else {
        printf("%.2f\n", result);
    }

    return 0;
}