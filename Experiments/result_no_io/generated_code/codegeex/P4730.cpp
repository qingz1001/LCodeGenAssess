#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define MAXM 4005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int v, w, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN * 2], dist[MAXN * 2], vis[MAXN * 2];
int n, m, k, d_min, d_max, cnt, ans[MAXN];

void addEdge(int u, int v, int w) {
    edges[cnt].v = v;
    edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void SPFA(int start) {
    int queue[MAXN * 2], front = 0, rear = 0;
    memset(dist, INF, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[start] = 0;
    vis[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];
        vis[u] = 0;
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v, w = edges[i].w;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!vis[v]) {
                    vis[v] = 1;
                    queue[rear++] = v;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%d%d", &d_min, &d_max);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        addEdge(i, i + n, 0);
        for (int j = 1; j < i; j++) {
            int dx = x - (i - j);
            int dy = y - (i - j);
            if (d_min <= dx + dy && dx + dy <= d_max) {
                addEdge(i, j, 1);
                addEdge(j, i, 1);
            }
        }
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
        int v, u;
        scanf("%d%d", &v, &u);
        SPFA(v);
        for (int j = 1; j <= k; j++) {
            if (i != j) {
                ans[i] = (ans[i] < dist[u + n] + 1) ? ans[i] : dist[u + n] + 1;
            }
        }
    }
    for (int i = 1; i <= k; i++) {
        printf("%d\n", (ans[i] == INF) ? -1 : ans[i]);
    }
    return 0;
}