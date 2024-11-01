#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5005
#define MAXM 100005
#define INF 0x3f3f3f3f

int n, m, k;
int head[MAXN], to[MAXM << 1], nxt[MAXM << 1], w[MAXM << 1], edge_cnt = 0;
int dis1[MAXN], dis2[MAXN], vis[MAXN];

void add(int u, int v, int ww) {
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    w[edge_cnt] = ww;
    head[u] = edge_cnt++;
}

void dijkstra(int start, int *dist) {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[start] = 0;

    for (int i = 1; i < n; i++) {
        int minn = INF, u = -1;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] < minn) {
                minn = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        vis[u] = 1;

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (dist[u] + w[e] < dist[v] && (v == n || v == start || head[v] > 1)) {
                dist[v] = dist[u] + w[e];
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    memset(head, -1, sizeof(head));

    for (int i = 0; i < m; i++) {
        int u, v, ww;
        scanf("%d%d%d", &u, &v, &ww);
        add(u, v, ww);
        add(v, u, ww);
    }

    dijkstra(1, dis1);
    if (dis1[n] == INF) {
        printf("-1\n");
        return 0;
    }

    // Add self-loops to nodes with less than k neighbors
    for (int i = 1; i <= n; i++) {
        int neighbor_count = 0;
        for (int e = head[i]; e != -1; e = nxt[e]) neighbor_count++;
        if (neighbor_count < k && i != 1 && i != n) {
            add(i, i, 0);
        }
    }

    dijkstra(1, dis2);

    if (dis2[n] == INF || dis2[n] == dis1[n]) {
        printf("-1\n");
    } else {
        printf("%d\n", dis2[n]);
    }

    return 0;
}