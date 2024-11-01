#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 0x3f3f3f3f
#define MAXN 105

int N, K, M, S, T;
int culture[MAXN];
int reject[MAXN][MAXN];
int dist[MAXN][MAXN];
int visited[MAXN];
int min_dist[MAXN];

void dijkstra() {
    memset(min_dist, INF, sizeof(min_dist));
    min_dist[S] = 0;

    for (int i = 1; i <= N; i++) {
        int u = -1;
        for (int j = 1; j <= N; j++) {
            if (!visited[j] && (u == -1 || min_dist[j] < min_dist[u])) {
                u = j;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= N; v++) {
            if (!visited[v] && dist[u][v] != INF) {
                int can_visit = 1;
                for (int k = 1; k <= N; k++) {
                    if (visited[k] && reject[culture[v]][culture[k]]) {
                        can_visit = 0;
                        break;
                    }
                }
                if (can_visit) {
                    min_dist[v] = (min_dist[v] < min_dist[u] + dist[u][v]) ? min_dist[v] : min_dist[u] + dist[u][v];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &N, &K, &M, &S, &T);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &culture[i]);
    }

    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= K; j++) {
            scanf("%d", &reject[i][j]);
        }
    }

    memset(dist, INF, sizeof(dist));
    for (int i = 1; i <= M; i++) {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        if (dist[u][v] > d) {
            dist[u][v] = d;
            dist[v][u] = d;
        }
    }

    dijkstra();

    if (min_dist[T] == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", min_dist[T]);
    }

    return 0;
}