#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50

int n, m, k;
int r[MAXN], d[MAXN];
int castles[MAXN];
int dist[MAXN];

void dijkstra(int start) {
    int visited[MAXN] = {0};
    for (int i = 0; i < n; i++) dist[i] = INT_MAX;
    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min = INT_MAX, min_index;
        for (int v = 0; v < n; v++)
            if (!visited[v] && dist[v] <= min)
                min = dist[v], min_index = v;

        visited[min_index] = 1;
        for (int v = 0; v < n; v++)
            if (!visited[v] && r[min_index] == v && dist[min_index] != INT_MAX && dist[min_index] + d[min_index] < dist[v])
                dist[v] = dist[min_index] + d[min_index];
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) scanf("%d", &r[i]);
    for (int i = 0; i < n; i++) scanf("%d", &d[i]);
    for (int i = 0; i < m; i++) scanf("%d", &castles[i]);

    int max_dist = INT_MIN;
    for (int i = 0; i < n; i++) {
        dijkstra(i);
        int min_dist = INT_MAX;
        for (int j = 0; j < m; j++) {
            if (dist[castles[j]] < min_dist) {
                min_dist = dist[castles[j]];
            }
        }
        if (min_dist > max_dist) {
            max_dist = min_dist;
        }
    }

    printf("%d\n", max_dist);
    return 0;
}