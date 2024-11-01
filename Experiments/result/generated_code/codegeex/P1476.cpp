#include <stdio.h>
#include <string.h>

#define MAXN 100
#define MAXM 120

int n, m;
int adj[MAXM][MAXM], cost[MAXM][MAXM];
int dist[MAXM], pre[MAXM];
bool inQueue[MAXM];

void dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist));
    memset(pre, -1, sizeof(pre));
    memset(inQueue, false, sizeof(inQueue));
    dist[start] = 0;

    for (int i = 0; i < m; i++) {
        int u = -1, minDist = 0x3f3f3f3f;
        for (int j = 0; j < m; j++) {
            if (!inQueue[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }
        if (u == -1) break;
        inQueue[u] = true;

        for (int v = 0; v < m; v++) {
            if (adj[u][v] && dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
                pre[v] = u;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(adj, 0, sizeof(adj));
    memset(cost, 0, sizeof(cost));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        adj[u][v] = 1;
        cost[u][v] = w;
    }

    dijkstra(0);

    int totalTime = dist[m-1];
    printf("%d\n", totalTime);

    int path[MAXM], pathLen = 0;
    for (int u = m-1; u != -1; u = pre[u]) {
        path[pathLen++] = u + 1;
    }

    for (int i = pathLen - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");

    return 0;
}