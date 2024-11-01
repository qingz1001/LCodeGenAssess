#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 200
#define MAX_M 9500
#define MAX_Q 50000

int n, m, q;
int t[MAX_N];
int graph[MAX_N][MAX_N];
int rebuild_time[MAX_N][MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

void floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][j] > graph[i][k] + graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = INT_MAX;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
        rebuild_time[u][v] = t[u] + t[v];
        rebuild_time[v][u] = t[u] + t[v];
    }
    floyd();
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);
        if (t < t[x] || t < t[y] || graph[x][y] == INT_MAX) {
            printf("-1\n");
        } else {
            printf("%d\n", graph[x][y]);
        }
    }
    return 0;
}