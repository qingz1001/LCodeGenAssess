#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 51
#define MAXM 1001
#define MAXQ 100001

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAXM];
int graph[MAXN][MAXN];
int dist[MAXN][MAXN];
int parent[MAXN][MAXN];

void addEdge(int u, int v, int w) {
    edges[u].u = u;
    edges[u].v = v;
    edges[u].w = w;
}

void floydWarshall(int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = k;
                }
            }
        }
    }
}

double findMinDensity(int x, int y) {
    if (dist[x][y] == 0) return -1; // No path exists
    int pathLength = 0;
    int u = x, v = y;
    while (u != v) {
        if (parent[u][v] == 0) {
            pathLength++;
        } else {
            int next = parent[u][v];
            pathLength += dist[u][next];
            u = next;
        }
    }
    return (double)dist[x][y] / pathLength;
}

int main() {
    int n, m, q;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(i, v, w);
        graph[u][v] = w;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = 1000000000; // A large number representing infinity
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (graph[i][j] != 0) dist[i][j] = graph[i][j];
        }
    }

    floydWarshall(n);

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        double minDensity = findMinDensity(x, y);
        if (minDensity == -1) printf("OMG!\n");
        else printf("%.3lf\n", minDensity);
    }

    return 0;
}