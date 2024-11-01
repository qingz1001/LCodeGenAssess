#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50
#define MAX_M 1250
#define INF 0x3f3f3f3f

int n, m, s, t, k;
int graph[MAX_N][MAX_N];
int blood[MAX_N][MAX_N];
int monster[MAX_N];

void dijkstra(int start, int end, int k) {
    int dist[MAX_N];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    for (int i = 0; i < k; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (dist[j] != INF && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (u == end) break;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && dist[v] > dist[u] + blood[u][v]) {
                dist[v] = dist[u] + blood[u][v];
            }
        }
    }

    printf("%d\n", dist[end]);
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
            blood[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u-1][v-1] = 1;
        graph[v-1][u-1] = 1;
        blood[u-1][v-1] = w;
        blood[v-1][u-1] = w;
    }

    int a;
    scanf("%d", &a);

    for (int i = 0; i < a; i++) {
        scanf("%d", &monster[i]);
    }

    dijkstra(s-1, t-1, k);

    return 0;
}