#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005
#define INF 0x3f3f3f3f

typedef struct {
    int to, w;
} Edge;

int n, s;
Edge edges[MAXN];
int degree[MAXN];
int dist[MAXN][2];

void dijkstra(int start) {
    for (int i = 1; i <= n; ++i) {
        dist[i][0] = dist[i][1] = INF;
    }
    dist[start][0] = 0;
    for (int k = 0; k < n - 1; ++k) {
        int u = -1, minDist = INF;
        for (int v = 1; v <= n; ++v) {
            if (!degree[v] && dist[v][0] < minDist) {
                u = v;
                minDist = dist[v][0];
            }
        }
        if (u == -1) break;
        degree[u]--;
        for (int i = 0; i < degree[u]; ++i) {
            int v = edges[edges[u].to + i].to;
            int w = edges[edges[u].to + i].w;
            if (dist[u][0] + w < dist[v][0]) {
                dist[v][1] = dist[v][0];
                dist[v][0] = dist[u][0] + w;
            } else if (dist[u][0] + w < dist[v][1]) {
                dist[v][1] = dist[u][0] + w;
            }
            degree[v]++;
        }
    }
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; ++i) {
        degree[i] = 0;
    }
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[i].to = u * n + v;
        edges[i].w = w;
        edges[i + n].to = v * n + u;
        edges[i + n].w = w;
        degree[u]++;
        degree[v]++;
    }

    int ans = INF;
    for (int i = 1; i <= n; ++i) {
        dijkstra(i);
        int maxDist = 0;
        for (int j = 1; j <= n; ++j) {
            maxDist = fmax(maxDist, fmin(dist[j][0], dist[j][1]));
        }
        if (maxDist <= s) {
            ans = fmin(ans, maxDist);
        }
    }

    printf("%d\n", ans);
    return 0;
}