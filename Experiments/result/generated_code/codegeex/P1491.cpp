#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 205
#define MAXM 10005

struct Edge {
    int u, v;
    double w;
};

int n, m;
struct Edge edges[MAXM];
double dist[MAXN][MAXN];
int prev[MAXN];
int visited[MAXN];

void addEdge(int u, int v, double w) {
    edges[m].u = u;
    edges[m].v = v;
    edges[m].w = w;
    m++;
}

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[start][i] = 999999999.0;
        prev[i] = -1;
        visited[i] = 0;
    }
    dist[start][start] = 0.0;

    for (int i = 1; i < n; i++) {
        int minDist = 999999999;
        int minNode = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[start][j] < minDist) {
                minDist = dist[start][j];
                minNode = j;
            }
        }
        if (minNode == -1) break;
        visited[minNode] = 1;

        for (int j = 0; j < m; j++) {
            if (edges[j].u == minNode && dist[start][edges[j].v] > dist[start][minNode] + edges[j].w) {
                dist[start][edges[j].v] = dist[start][minNode] + edges[j].w;
                prev[edges[j].v] = minNode;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        double x, y;
        scanf("%lf %lf", &x, &y);
        for (int j = 1; j < i; j++) {
            double d = sqrt((x - dist[j][i]) * (x - dist[j][i]) + (y - dist[j][i]) * (y - dist[j][i]));
            addEdge(i, j, d);
            addEdge(j, i, d);
        }
    }

    dijkstra(1);

    double shortestPath = dist[1][n];
    int current = n;
    while (current != -1) {
        current = prev[current];
    }

    dijkstra(1);

    double secondShortestPath = dist[1][n];
    if (secondShortestPath >= shortestPath) {
        printf("-1\n");
    } else {
        printf("%.2lf\n", secondShortestPath);
    }

    return 0;
}