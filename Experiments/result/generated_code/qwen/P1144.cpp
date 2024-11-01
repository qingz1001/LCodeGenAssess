#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001
#define MOD 100003

int n, m;
int graph[MAXN][MAXN];
int dist[MAXN];
int path_count[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
        path_count[i] = 0;
    }
    dist[start] = 0;
    path_count[start] = 1;

    int visited[MAXN] = {0};
    while (1) {
        int min_dist = -1;
        int min_node = -1;
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && dist[i] != -1 && (min_dist == -1 || dist[i] < min_dist)) {
                min_dist = dist[i];
                min_node = i;
            }
        }
        if (min_node == -1) break;
        visited[min_node] = 1;

        for (int j = 1; j <= n; j++) {
            if (graph[min_node][j] != -1 && dist[j] == -1) {
                dist[j] = dist[min_node] + graph[min_node][j];
                path_count[j] = path_count[min_node];
            } else if (graph[min_node][j] != -1 && dist[j] == dist[min_node] + graph[min_node][j]) {
                path_count[j] = (path_count[j] + path_count[min_node]) % MOD;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = -1;
        }
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (graph[x][y] == -1) {
            graph[x][y] = 1;
            graph[y][x] = 1;
        } else {
            graph[x][y]++;
            graph[y][x]++;
        }
    }

    dijkstra(1);

    for (int i = 1; i <= n; i++) {
        printf("%d\n", path_count[i]);
    }

    return 0;
}