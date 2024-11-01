#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001
#define MOD 100003

int n, m;
int graph[MAXN][MAXN];
int dist[MAXN], path_cnt[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX / 2;
        path_cnt[i] = 0;
    }
    dist[start] = 0;
    path_cnt[start] = 1;

    int visited[MAXN] = {0};
    while (1) {
        int min_dist = INT_MAX / 2, u = -1;
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (graph[u][v] != 0 && !visited[v]) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    path_cnt[v] = path_cnt[u];
                } else if (dist[u] + graph[u][v] == dist[v]) {
                    path_cnt[v] = (path_cnt[v] + path_cnt[u]) % MOD;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x][y]++;
        graph[y][x]++;
    }

    dijkstra(1);

    for (int i = 1; i <= n; i++) {
        printf("%d\n", path_cnt[i]);
    }

    return 0;
}