#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 51
#define MAX_M 1251
#define MAX_A 31

int n, m, s, t, k;
int graph[MAX_N][MAX_N];
int dist[MAX_N];
int monsters[MAX_A][4];
int monster_count;

void dijkstra(int start, int time) {
    int visited[MAX_N] = {0};
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    for (int i = 1; i <= n; i++) {
        int min_dist = INT_MAX, u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (graph[u][v] > 0) {
                int monster_present = 0;
                for (int m = 0; m < monster_count; m++) {
                    int period = monsters[m][0];
                    if (monsters[m][(time + 1) % period + 1] == v) {
                        monster_present = 1;
                        break;
                    }
                }
                if (!monster_present && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &k);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = graph[v][u] = w;
    }

    scanf("%d", &monster_count);
    for (int i = 0; i < monster_count; i++) {
        scanf("%d", &monsters[i][0]);
        for (int j = 1; j <= monsters[i][0]; j++) {
            scanf("%d", &monsters[i][j]);
        }
    }

    int min_blood = INT_MAX;
    for (int time = 0; time < k; time++) {
        dijkstra(s, time);
        if (dist[t] < min_blood) {
            min_blood = dist[t];
        }
    }

    if (min_blood == INT_MAX) {
        printf("IMP0SSBLE!!\n");
    } else {
        printf("%d\n", min_blood);
    }

    return 0;
}