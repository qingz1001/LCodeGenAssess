#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INF 0x3f3f3f3f

typedef struct {
    int u, v, w, next;
} Edge;

int n, m, head[1000010], cnt, dis[1000010], vis[1000010];
Edge edge[1000010];

void add(int u, int v, int w) {
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void dijkstra(int start) {
    for (int i = 0; i <= m; i++) {
        dis[i] = INF;
        vis[i] = 0;
    }
    dis[start] = 0;
    for (int i = 0; i < m; i++) {
        int minn = INF, k = -1;
        for (int j = 0; j <= m; j++) {
            if (!vis[j] && dis[j] < minn) {
                minn = dis[j];
                k = j;
            }
        }
        if (k == -1) break;
        vis[k] = 1;
        for (int j = head[k]; j != -1; j = edge[j].next) {
            int v = edge[j].v;
            if (dis[v] > dis[k] + edge[j].w) {
                dis[v] = dis[k] + edge[j].w;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    m = n * n + 1;
    memset(head, -1, sizeof(head));
    int u, v, w;
    for (int i = 1; i <= n * n; i++) {
        scanf("%d", &w);
        add(i, i + 1, w);
        add(i + 1, i, w);
    }
    for (int i = 1; i <= n * n; i++) {
        scanf("%d", &w);
        add(i, i + n, w);
        add(i + n, i, w);
    }
    for (int i = 1; i <= n * n; i++) {
        scanf("%d", &w);
        add(i, i - 1, w);
        add(i - 1, i, w);
    }
    for (int i = 1; i <= n * n; i++) {
        scanf("%d", &w);
        add(i, i - n, w);
        add(i - n, i, w);
    }
    dijkstra(1);
    printf("%d\n", dis[m]);
    return 0;
}