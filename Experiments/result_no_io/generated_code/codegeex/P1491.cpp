#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 205
#define MAXM 10005

int n, m;
int x[MAXN], y[MAXN];
int adj[MAXN][MAXN];
int dis[MAXN][2];
int vis[MAXN];

void dijkstra(int start) {
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));
    dis[start][0] = 0;

    for (int i = 0; i < n; i++) {
        int min = INT_MAX, u = -1;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && (u == -1 || dis[j][0] < min)) {
                min = dis[j][0];
                u = j;
            }
        }
        if (u == -1) break;
        vis[u] = 1;

        for (int v = 0; v < n; v++) {
            if (adj[u][v] && dis[u][0] + adj[u][v] < dis[v][0]) {
                dis[v][0] = dis[u][0] + adj[u][v];
            }
            if (adj[u][v] && dis[u][0] + adj[u][v] < dis[v][1] && dis[u][0] + adj[u][v] != dis[v][0]) {
                dis[v][1] = dis[u][0] + adj[u][v];
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        adj[u][v] = adj[v][u] = 1;
    }

    dijkstra(0);

    if (dis[n-1][1] == 0x3f3f3f3f) {
        printf("-1\n");
    } else {
        printf("%.2f\n", (double)dis[n-1][1]);
    }

    return 0;
}