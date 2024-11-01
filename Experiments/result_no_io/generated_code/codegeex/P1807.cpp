#include <stdio.h>
#include <limits.h>

#define MAXN 1500
#define MAXM 50000

int n, m;
int dist[MAXN + 1];
int head[MAXN + 1];
int to[MAXM + 1], next[MAXM + 1], weight[MAXM + 1];

void addEdge(int u, int v, int w) {
    static int edgeCount = 0;
    to[edgeCount] = v;
    weight[edgeCount] = w;
    next[edgeCount] = head[u];
    head[u] = edgeCount++;
}

void BellmanFord() {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MIN;
    }
    dist[1] = 0;

    for (int i = 1; i < n; i++) {
        for (int u = 1; u <= n; u++) {
            for (int e = head[u]; e != -1; e = next[e]) {
                int v = to[e];
                int w = weight[e];
                if (dist[u] != INT_MIN && dist[u] + w > dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    for (int u = 1; u <= n; u++) {
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];
            int w = weight[e];
            if (dist[u] != INT_MIN && dist[u] + w > dist[v]) {
                dist[v] = INT_MIN;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) {
        head[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
    }

    BellmanFord();

    if (dist[n] == INT_MIN) {
        printf("-1\n");
    } else {
        printf("%d\n", dist[n]);
    }

    return 0;
}