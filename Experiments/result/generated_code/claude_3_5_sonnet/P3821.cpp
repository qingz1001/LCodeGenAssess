#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_N 51
#define MAX_M 1251
#define INF 0x3f3f3f3f

int n, m, s, t, k, a;
int graph[MAX_N][MAX_N];
int dist[MAX_N];
int monster[31][5];
int monster_pos[31];
int T[31];

void dijkstra(int src) {
    int visited[MAX_N] = {0};
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (dist[u] == INF) break;
        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (graph[u][v] != INF) {
                int new_dist = (dist[u] > graph[u][v]) ? dist[u] : graph[u][v];
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                }
            }
        }
    }
}

int is_safe(int node, int time) {
    for (int i = 0; i < a; i++) {
        if (monster[i][monster_pos[i]] == node) {
            return 0;
        }
        monster_pos[i] = (monster_pos[i] + 1) % T[i];
    }
    return 1;
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &k);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = INF;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = graph[v][u] = w;
    }

    scanf("%d", &a);
    for (int i = 0; i < a; i++) {
        scanf("%d", &T[i]);
        for (int j = 0; j < T[i]; j++) {
            scanf("%d", &monster[i][j]);
        }
    }

    dijkstra(s);

    if (dist[t] == INF || !is_safe(s, 0)) {
        printf("IMP0SSBLE!!\n");
        return 0;
    }

    int current = s;
    for (int time = 1; time <= k; time++) {
        int next = -1;
        for (int v = 1; v <= n; v++) {
            if (graph[current][v] != INF && dist[v] == dist[t] && is_safe(v, time)) {
                next = v;
                break;
            }
        }
        if (next == -1) {
            printf("IMP0SSBLE!!\n");
            return 0;
        }
        if (next == t && time == k) {
            printf("%d\n", dist[t]);
            return 0;
        }
        current = next;
    }

    printf("IMP0SSBLE!!\n");
    return 0;
}