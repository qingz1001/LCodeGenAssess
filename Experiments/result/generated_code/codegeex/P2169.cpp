#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 200005
#define MAXM 1000005

int n, m;
int head[MAXN], next[MAXM], ver[MAXM], edge[MAXM];
int dist[MAXN];
bool vis[MAXN];

void add(int x, int y, int z) {
    static int tot = 0;
    ver[tot] = y;
    edge[tot] = z;
    next[tot] = head[x];
    head[x] = tot++;
}

void spfa() {
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    vis[1] = true;
    for (int i = 0; i < n; i++) {
        int u = -1, minn = INT_MAX;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] < minn) {
                u = j;
                minn = dist[j];
            }
        }
        if (u == -1) break;
        vis[u] = true;
        for (int j = head[u]; j != -1; j = next[j]) {
            int v = ver[j], w = edge[j];
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
    }
    spfa();
    printf("%d\n", dist[n]);
    return 0;
}