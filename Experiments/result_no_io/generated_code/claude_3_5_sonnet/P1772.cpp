#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 101
#define MAX_M 21
#define INF 0x3f3f3f3f

int n, m, k, e, d;
int graph[MAX_M][MAX_M];
int closed[MAX_M][MAX_N];
int dist[MAX_M];
int visited[MAX_M];
int prev_path[MAX_M];
int curr_path[MAX_M];

void dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    dist[start] = 0;

    for (int i = 1; i <= m; i++) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= m; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= m; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev_path[v] = u;
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &e);

    memset(graph, 0x3f, sizeof(graph));
    for (int i = 0; i < e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = graph[v][u] = w;
    }

    scanf("%d", &d);
    for (int i = 0; i < d; i++) {
        int p, a, b;
        scanf("%d %d %d", &p, &a, &b);
        for (int j = a; j <= b; j++) {
            closed[p][j] = 1;
        }
    }

    int total_cost = 0;
    int changes = 0;

    for (int day = 1; day <= n; day++) {
        for (int i = 1; i <= m; i++) {
            if (closed[i][day]) {
                for (int j = 1; j <= m; j++) {
                    graph[i][j] = graph[j][i] = INF;
                }
            }
        }

        dijkstra(1);

        if (day > 1) {
            int different = 0;
            for (int i = m; i != 1; i = prev_path[i]) {
                if (i != curr_path[i]) {
                    different = 1;
                    break;
                }
            }
            if (different) {
                changes++;
            }
        }

        total_cost += dist[m];

        for (int i = m; i != 1; i = prev_path[i]) {
            curr_path[i] = prev_path[i];
        }

        for (int i = 1; i <= m; i++) {
            if (closed[i][day]) {
                for (int j = 1; j <= m; j++) {
                    graph[i][j] = graph[j][i] = INF;
                }
            }
        }
    }

    total_cost += changes * k;
    printf("%d\n", total_cost);

    return 0;
}