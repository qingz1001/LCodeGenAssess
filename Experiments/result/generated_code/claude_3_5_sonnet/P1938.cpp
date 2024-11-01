#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_C 221
#define MAX_F 351
#define INF 0x3f3f3f3f

int D, P, C, F, S;
int dist[MAX_C];
bool vis[MAX_C];
int graph[MAX_C][MAX_C];

void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    dist[S] = 0;

    for (int i = 1; i <= C; i++) {
        int u = -1;
        for (int j = 1; j <= C; j++) {
            if (!vis[j] && (u == -1 || dist[j] > dist[u])) {
                u = j;
            }
        }
        if (u == -1) break;
        vis[u] = true;

        for (int v = 1; v <= C; v++) {
            if (graph[u][v] != INF) {
                dist[v] = (dist[v] > dist[u] + graph[u][v]) ? dist[v] : dist[u] + graph[u][v];
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &D, &P, &C, &F, &S);

    memset(graph, 0x3f, sizeof(graph));
    for (int i = 1; i <= C; i++) {
        graph[i][i] = 0;
    }

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

    int max_profit = 0;
    bool has_positive_cycle = false;

    for (int i = 1; i <= C; i++) {
        if (dist[i] == INF) continue;
        int profit = -dist[i];
        if (profit > max_profit) {
            max_profit = profit;
        }
        for (int j = 1; j <= C; j++) {
            if (graph[i][j] != INF && dist[j] - dist[i] > graph[i][j]) {
                has_positive_cycle = true;
                break;
            }
        }
        if (has_positive_cycle) break;
    }

    if (has_positive_cycle) {
        printf("-1\n");
    } else {
        int total_profit = (max_profit / D) * D;
        printf("%d\n", total_profit);
    }

    return 0;
}