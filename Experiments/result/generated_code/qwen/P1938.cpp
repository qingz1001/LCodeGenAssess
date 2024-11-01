#include <stdio.h>
#include <stdlib.h>

#define MAX_CITIES 220
#define MAX_PATHS 150
#define MAX_ROUTES 350
#define INF 1000000000

int D, P, C, F, S;
int paths[MAX_PATHS][2];
int routes[MAX_ROUTES][3];
int dp[MAX_CITIES];

void dijkstra(int start, int *dist) {
    for (int i = 0; i < C; i++) dist[i] = INF;
    dist[start] = 0;
    for (int i = 0; i < C - 1; i++) {
        for (int j = 0; j < P; j++) {
            int u = paths[j][0], v = paths[j][1];
            if (dist[u] != INF && dist[v] > dist[u]) {
                dist[v] = dist[u];
            }
        }
        for (int j = 0; j < F; j++) {
            int u = routes[j][0], v = routes[j][1], w = routes[j][2];
            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &D, &P, &C, &F, &S);
    for (int i = 0; i < P; i++) {
        scanf("%d %d", &paths[i][0], &paths[i][1]);
    }
    for (int i = 0; i < F; i++) {
        scanf("%d %d %d", &routes[i][0], &routes[i][1], &routes[i][2]);
    }

    int minDist[C];
    dijkstra(S, minDist);

    int maxProfit = -1;
    for (int i = 0; i < C; i++) {
        if (minDist[i] == INF) continue;
        int profit = (D / minDist[i]) * minDist[i];
        if (profit > maxProfit) maxProfit = profit;
    }

    printf("%d\n", maxProfit);
    return 0;
}