#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200
#define MAXM 160000

struct Edge {
    int u, v, w;
} edges[MAXM];

int dist[MAXN][MAXN];
int pre[MAXN][MAXN];
int important[MAXN];
int n, m;

void dijkstra(int start) {
    int visited[MAXN] = {0};
    for (int i = 0; i < n; i++) {
        dist[start][i] = INT_MAX;
    }
    dist[start][start] = 0;

    for (int i = 0; i < n; i++) {
        int minDist = INT_MAX;
        int minNode = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[start][j] < minDist) {
                minDist = dist[start][j];
                minNode = j;
            }
        }
        if (minNode == -1) break;
        visited[minNode] = 1;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[start][minNode] + edges[pre[start][minNode]].w < dist[start][j]) {
                dist[start][j] = dist[start][minNode] + edges[pre[start][minNode]].w;
                pre[start][j] = pre[start][minNode];
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(pre, -1, sizeof(pre));

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        pre[edges[i].u][edges[i].v] = i;
        pre[edges[i].v][edges[i].u] = i;
    }

    for (int i = 0; i < n; i++) {
        dijkstra(i);
    }

    int hasImportantCity = 0;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (i == k) continue;
            for (int j = 0; j < n; j++) {
                if (j == k || i == j) continue;
                if (dist[i][k] + dist[k][j] == dist[i][j]) {
                    important[k] = 1;
                    hasImportantCity = 1;
                }
            }
        }
    }

    if (!hasImportantCity) {
        printf("No important cities.\n");
    } else {
        for (int i = 0; i < n; i++) {
            if (important[i]) {
                printf("%d ", i);
            }
        }
        printf("\n");
    }

    return 0;
}