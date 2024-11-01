#include <stdio.h>
#include <stdlib.h>

#define MAXN 205
#define INF 1e9

int n, m, k, q;
double u[MAXN];
int v[MAXN], w[MAXN], r[MAXN];

void dijkstra(int start, double dist[]) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;
    for (int i = 1; i <= n; i++) {
        int min_dist = INF, min_index = -1;
        for (int j = 1; j <= n; j++) {
            if (dist[j] < min_dist && !visited[j]) {
                min_dist = dist[j];
                min_index = j;
            }
        }
        visited[min_index] = 1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[min_index] + r[min_index][j] < dist[j]) {
                dist[j] = dist[min_index] + r[min_index][j];
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &q);
    for (int i = 1; i <= k; i++) {
        int id, value;
        scanf("%d %d", &id, &value);
        u[id] = value;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &v[i], &w[i], &r[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) r[i][j] = 0;
            else r[i][j] = INF;
        }
    }
    for (int i = 1; i <= m; i++) {
        r[v[i]][w[i]] = r[w[i]][v[i]] = r[i];
    }
    for (int i = 1; i <= n; i++) {
        dijkstra(i, d[i]);
    }
    for (int i = 1; i <= q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%.2f\n", d[a][b] - d[b][a]);
    }
    return 0;
}