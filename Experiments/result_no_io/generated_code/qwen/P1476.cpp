#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 120

int n, m;
int graph[MAX_N + 1][MAX_N + 1];
int visited[MAX_N + 1];
int time[MAX_N + 1];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
        time[i] = INT_MAX;
    }
    time[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && (u == -1 || time[v] < time[u])) {
                u = v;
            }
        }

        visited[u] = 1;
        for (int v = 1; v <= n; v++) {
            if (graph[u][v] != 0 && !visited[v]) {
                if (time[u] + graph[u][v] < time[v]) {
                    time[v] = time[u] + graph[u][v];
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
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        graph[u][v] = k;
    }

    int min_time = INT_MAX;
    for (int i = 1; i <= n; i++) {
        dijkstra(i);
        int max_time = 0;
        for (int j = 1; j <= n; j++) {
            if (time[j] > max_time) {
                max_time = time[j];
            }
        }
        if (max_time < min_time) {
            min_time = max_time;
        }
    }

    printf("%d\n", min_time);

    return 0;
}