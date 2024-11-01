#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_P 800
#define MAX_C 1450

typedef struct {
    int to, weight;
} Edge;

typedef struct {
    int v, dist;
} Node;

int N, P, C;
int cows[500];
int dist[MAX_P + 1];
int visited[MAX_P + 1];
Edge edges[MAX_C * 2];
int adj[MAX_P + 1][MAX_P + 1];

void dijkstra(int start) {
    for (int i = 1; i <= P; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int i = 1; i <= P; i++) {
        int minDist = INT_MAX, u = -1;
        for (int j = 1; j <= P; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int j = 1; j <= P; j++) {
            if (!visited[j] && adj[u][j] && dist[u] + adj[u][j] < dist[j]) {
                dist[j] = dist[u] + adj[u][j];
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &P, &C);
    for (int i = 0; i < N; i++) {
        scanf("%d", &cows[i]);
    }
    for (int i = 0; i < C; i++) {
        int A, B, D;
        scanf("%d %d %d", &A, &B, &D);
        adj[A][B] = D;
        adj[B][A] = D;
    }

    int minTotalDist = INT_MAX;
    for (int i = 1; i <= P; i++) {
        dijkstra(i);
        int totalDist = 0;
        for (int j = 0; j < N; j++) {
            totalDist += dist[cows[j]];
        }
        if (totalDist < minTotalDist) {
            minTotalDist = totalDist;
        }
    }

    printf("%d\n", minTotalDist);
    return 0;
}