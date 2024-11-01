#include <stdio.h>
#include <string.h>

#define MAXN 1000001
#define MAXM 2000001
#define INF 0x3f3f3f3f

typedef struct {
    int v, w;
} Edge;

Edge edges[MAXM];
int head[MAXN], dist[MAXN], vis[MAXN];
int n, m, cnt;

void addEdge(int u, int v, int w) {
    edges[cnt].v = v;
    edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void spfa(int start) {
    memset(dist, INF, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[start] = 0;
    vis[start] = 1;
    int queue[MAXN], front = 0, rear = 0;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];
        vis[u] = 0;
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v;
            if (dist[u] + edges[i].w < dist[v]) {
                dist[v] = dist[u] + edges[i].w;
                if (!vis[v]) {
                    vis[v] = 1;
                    queue[rear++] = v;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    spfa(1);
    long long totalCost = 0;
    for (int i = 1; i <= n; i++) {
        totalCost += dist[i];
    }

    printf("%lld\n", totalCost);
    return 0;
}