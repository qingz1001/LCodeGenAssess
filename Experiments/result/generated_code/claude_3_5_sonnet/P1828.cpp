#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 500
#define MAX_P 800
#define MAX_C 1450
#define INF INT_MAX

int N, P, C;
int cows[MAX_N];
int dist[MAX_P+1][MAX_P+1];
int minDist[MAX_P+1];
int visited[MAX_P+1];

void dijkstra(int start) {
    for (int i = 1; i <= P; i++) {
        minDist[i] = INF;
        visited[i] = 0;
    }
    minDist[start] = 0;

    for (int i = 0; i < P; i++) {
        int u = -1;
        int minD = INF;
        for (int j = 1; j <= P; j++) {
            if (!visited[j] && minDist[j] < minD) {
                u = j;
                minD = minDist[j];
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= P; v++) {
            if (!visited[v] && dist[u][v] != INF) {
                if (minDist[u] + dist[u][v] < minDist[v]) {
                    minDist[v] = minDist[u] + dist[u][v];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &P, &C);

    for (int i = 0; i < N; i++) {
        scanf("%d", &cows[i]);
    }

    for (int i = 1; i <= P; i++) {
        for (int j = 1; j <= P; j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }

    for (int i = 0; i < C; i++) {
        int a, b, d;
        scanf("%d %d %d", &a, &b, &d);
        dist[a][b] = dist[b][a] = d;
    }

    int minTotalDist = INF;
    for (int i = 1; i <= P; i++) {
        dijkstra(i);
        int totalDist = 0;
        for (int j = 0; j < N; j++) {
            totalDist += minDist[cows[j]];
        }
        if (totalDist < minTotalDist) {
            minTotalDist = totalDist;
        }
    }

    printf("%d\n", minTotalDist);

    return 0;
}