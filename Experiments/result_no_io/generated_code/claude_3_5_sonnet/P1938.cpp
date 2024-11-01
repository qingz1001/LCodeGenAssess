#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CITIES 220
#define MAX_PATHS 150
#define MAX_FLIGHTS 350
#define INF 0x3f3f3f3f

int D, P, C, F, S;
int graph[MAX_CITIES][MAX_CITIES];
int dist[MAX_CITIES];
bool visited[MAX_CITIES];

void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, false, sizeof(visited));
    dist[S] = 0;

    for (int i = 0; i < C; i++) {
        int u = -1;
        for (int j = 1; j <= C; j++) {
            if (!visited[j] && (u == -1 || dist[j] > dist[u])) {
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = true;

        for (int v = 1; v <= C; v++) {
            if (graph[u][v] != INF) {
                int newDist = dist[u] + graph[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &D, &P, &C, &F, &S);

    memset(graph, 0x3f, sizeof(graph));

    for (int i = 0; i < P; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = 0;
    }

    for (int i = 0; i < F; i++) {
        int j, k, t;
        scanf("%d %d %d", &j, &k, &t);
        graph[j][k] = -t;
    }

    dijkstra();

    int minDist = INF;
    for (int i = 1; i <= C; i++) {
        if (dist[i] < minDist) {
            minDist = dist[i];
        }
    }

    if (minDist == -INF) {
        printf("-1\n");
    } else {
        int maxMoney = C * D + minDist;
        printf("%d\n", maxMoney);
    }

    return 0;
}