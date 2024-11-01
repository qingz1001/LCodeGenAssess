#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 150
#define MAXM 5000
#define INF 0x3f3f3f3f

typedef struct {
    int to;
    int speed;
    int length;
    int next;
} Edge;

Edge edges[MAXM + 5];
int head[MAXN + 5];
int dist[MAXN + 5];
int pre[MAXN + 5];
int vis[MAXN + 5];
int path[MAXN + 5];
int pathLen;

void addEdge(int u, int v, int speed, int length) {
    static int tot = 0;
    edges[++tot] = (Edge){v, speed, length, head[u]};
    head[u] = tot;
}

void dijkstra(int n, int start) {
    memset(dist, INF, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[start] = 0;
    pre[start] = -1;

    for (int i = 0; i < n; i++) {
        int u = -1, minDist = INF;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }
        if (u == -1) break;
        vis[u] = 1;

        for (int i = head[u]; i; i = edges[i].next) {
            int v = edges[i].to;
            int speed = edges[i].speed;
            int length = edges[i].length;
            int time;
            if (speed != 0) {
                time = length * 3600 / speed;
            } else {
                time = length * 3600 / 70;
            }
            if (dist[u] + time < dist[v]) {
                dist[v] = dist[u] + time;
                pre[v] = u;
            }
        }
    }
}

void printPath(int v) {
    if (v == -1) return;
    printPath(pre[v]);
    path[pathLen++] = v;
}

int main() {
    int n, m, d;
    scanf("%d %d %d", &n, &m, &d);

    for (int i = 0; i < m; i++) {
        int a, b, v, l;
        scanf("%d %d %d %d", &a, &b, &v, &l);
        addEdge(a, b, v, l);
    }

    dijkstra(n, 0);

    pathLen = 0;
    printPath(d);

    printf("0");
    for (int i = 1; i < pathLen; i++) {
        printf(" %d", path[i]);
    }
    printf("\n");

    return 0;
}