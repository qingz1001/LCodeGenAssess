#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10
#define MAXW 500
#define MAXH 500
#define MAXQ 1000000
#define MAXV (MAXN * MAXN)
#define MAXE (MAXV * 4)
#define INF 0x3f3f3f3f

int n, w, h;
char grid[MAXH][MAXW];
int start[MAXN], end[MAXN], dist[MAXN];
int head[MAXV], to[MAXE], next[MAXE], edgeCnt;

void addEdge(int u, int v) {
    to[edgeCnt] = v;
    next[edgeCnt] = head[u];
    head[u] = edgeCnt++;
}

int dijkstra(int start, int end) {
    int vis[MAXV], dis[MAXV];
    memset(vis, 0, sizeof(vis));
    memset(dis, INF, sizeof(dis));
    dis[start] = 0;
    int pq[MAXQ], pql, pqr;
    pq[0] = start;
    pql = pqr = 0;
    while (pql <= pqr) {
        int u = pq[pql++];
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i != -1; i = next[i]) {
            int v = to[i];
            if (dis[u] + 1 < dis[v]) {
                dis[v] = dis[u] + 1;
                pq[++pqr] = v;
            }
        }
    }
    return dis[end];
}

int main() {
    scanf("%d%d%d", &n, &w, &h);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < h; i++) {
        scanf("%s", grid[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < w; k++) {
                if (grid[j][k] == '0' + i + 1) {
                    start[i] = j * w + k;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                end[i] = start[i];
                dist[i] = 0;
            } else {
                int u = start[i];
                int v = start[j];
                int du = dijkstra(u, v);
                int dv = dijkstra(v, u);
                if (du < INF || dv < INF) {
                    end[i] = end[j] = u < v ? u : v;
                    dist[i] = dist[j] = du < dv ? du : dv;
                    addEdge(i, j);
                    addEdge(j, i);
                }
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j || (k != n - 1 && (i == k || j == k))) continue;
                if (dist[i] != INF && dist[j] != INF && dist[i] + dist[j] + 1 < dist[k]) {
                    dist[k] = dist[i] + dist[j] + 1;
                    end[k] = end[i] < end[j] ? end[i] : end[j];
                    addEdge(i, k);
                    addEdge(j, k);
                }
            }
        }
    }

    int ans = INF;
    for (int i = 0; i < n; i++) {
        if (dist[i] != INF && end[i] == start[n - 1]) {
            ans = dist[i];
            break;
        }
    }

    if (ans == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }

    return 0;
}