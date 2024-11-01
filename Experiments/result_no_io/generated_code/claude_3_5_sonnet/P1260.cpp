#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MAX_M 5001
#define INF 0x3f3f3f3f

int n, m;
int dist[MAX_N];
struct Edge {
    int from, to, weight;
} edges[MAX_M];

void bellman_ford() {
    memset(dist, 0x3f, sizeof(dist));
    dist[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = edges[j].from;
            int v = edges[j].to;
            int w = edges[j].weight;
            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int j = 0; j < m; j++) {
        int u = edges[j].from;
        int v = edges[j].to;
        int w = edges[j].weight;
        if (dist[u] != INF && dist[v] > dist[u] + w) {
            printf("NO SOLUTION\n");
            exit(0);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[i].from = v;
        edges[i].to = u;
        edges[i].weight = w;
    }

    for (int i = 1; i <= n; i++) {
        edges[m + i - 1].from = 0;
        edges[m + i - 1].to = i;
        edges[m + i - 1].weight = 0;
    }

    m += n;
    n++;

    bellman_ford();

    int min_dist = INF;
    for (int i = 1; i < n; i++) {
        if (dist[i] < min_dist) {
            min_dist = dist[i];
        }
    }

    for (int i = 1; i < n; i++) {
        printf("%d\n", dist[i] - min_dist);
    }

    return 0;
}