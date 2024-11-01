#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 30000
#define MAXM 150000
#define MAXR 10

typedef struct {
    int a, b, t;
} Edge;

int n, m;
int rank[MAXN];
Edge edges[MAXM];
int dist[MAXN][MAXN];
int B[MAXN];

void floyd_warshall() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < m; i++) {
        int a = edges[i].a;
        int b = edges[i].b;
        int t = edges[i].t;
        dist[a][b] = t;
        dist[b][a] = t;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &rank[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].t);
        edges[i].a--;
        edges[i].b--;
    }

    floyd_warshall();

    for (int v = 0; v < n; v++) {
        B[v] = 0;
        for (int w = 0; w < n; w++) {
            int interested = 1;
            for (int u = 0; u < n; u++) {
                if (rank[u] > rank[w] && dist[v][u] <= dist[v][w]) {
                    interested = 0;
                    break;
                }
            }
            if (interested) {
                B[v]++;
            }
        }
    }

    int total_storage = 0;
    for (int v = 0; v < n; v++) {
        total_storage += B[v];
    }

    printf("%d\n", total_storage);

    return 0;
}