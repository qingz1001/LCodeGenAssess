#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 5005
#define MAXM 100005
#define INF INT_MAX

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], cnt = 0;
int n, m, k;
int dist[MAXN], dist2[MAXN];
bool vis[MAXN];

void addEdge(int u, int v, int w) {
    edges[cnt].v = v;
    edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = dist2[i] = INF;
        vis[i] = false;
    }
    dist[start] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, minDist = INF;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }
        if (u == -1) break;
        vis[u] = true;

        for (int j = head[u]; j != -1; j = edges[j].next) {
            int v = edges[j].v, w = edges[j].w;
            if (dist[v] > dist[u] + w) {
                dist2[v] = dist[v];
                dist[v] = dist[u] + w;
            } else if (dist[v] != dist[u] + w && dist2[v] > dist[u] + w) {
                dist2[v] = dist[u] + w;
            }
            if (dist2[v] > dist2[u] + w) {
                dist2[v] = dist2[u] + w;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) head[i] = -1;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    dijkstra(1);

    if (dist2[n] == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", dist2[n]);
    }

    return 0;
}