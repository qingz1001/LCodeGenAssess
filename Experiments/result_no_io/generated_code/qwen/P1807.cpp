#include <stdio.h>
#include <stdlib.h>

#define MAXN 1501
#define INF -1

typedef struct {
    int to;
    int weight;
} Edge;

Edge edges[50001];
int adj[MAXN][MAXN];
int dist[MAXN];

void addEdge(int u, int v, int w) {
    edges[m++] = (Edge){v, w};
    adj[u][v] = w;
}

int longestPath(int n, int m) {
    for (int i = 1; i <= n; ++i)
        dist[i] = INF;
    dist[1] = 0;

    for (int k = 1; k <= n - 1; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INF)
                continue;
            for (int j = 1; j <= m; ++j) {
                int u = edges[j].to;
                int w = edges[j].weight;
                if (adj[i][u] != 0 && dist[i] + w > dist[u])
                    dist[u] = dist[i] + w;
            }
        }
    }

    return dist[n];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    int result = longestPath(n, m);
    printf("%d\n", result);

    return 0;
}