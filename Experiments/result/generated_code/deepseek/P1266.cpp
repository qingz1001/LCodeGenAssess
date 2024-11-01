#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 150
#define INF INT_MAX

typedef struct {
    int dest;
    int speed;
    int length;
} Road;

Road roads[MAXN][MAXN];
int dist[MAXN];
int prev[MAXN];
int visited[MAXN];
int N, M, D;

void dijkstra() {
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[0] = 0;
    prev[0] = -1;

    for (int count = 0; count < N - 1; count++) {
        int minDist = INF;
        int u = -1;

        for (int v = 0; v < N; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < N; v++) {
            if (!visited[v] && roads[u][v].length > 0) {
                int speed = roads[u][v].speed > 0 ? roads[u][v].speed : 70;
                int time = roads[u][v].length / speed;
                if (dist[u] + time < dist[v]) {
                    dist[v] = dist[u] + time;
                    prev[v] = u;
                }
            }
        }
    }
}

void printPath(int dest) {
    if (prev[dest] != -1) {
        printPath(prev[dest]);
    }
    printf("%d ", dest);
}

int main() {
    scanf("%d %d %d", &N, &M, &D);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            roads[i][j].length = 0;
        }
    }

    for (int i = 0; i < M; i++) {
        int A, B, V, L;
        scanf("%d %d %d %d", &A, &B, &V, &L);
        roads[A][B].dest = B;
        roads[A][B].speed = V;
        roads[A][B].length = L;
    }

    dijkstra();

    printPath(D);
    printf("\n");

    return 0;
}