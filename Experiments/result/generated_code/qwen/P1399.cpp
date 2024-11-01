#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100005
#define INF 1e18

typedef long long ll;

struct Edge {
    int to, next;
    ll dist;
} edge[MAXN * 2];

int head[MAXN], tot = 0;
ll dis[MAXN];
bool vis[MAXN];

void add(int u, int v, ll w) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].dist = w;
    head[u] = tot++;
}

void dijkstra(int start) {
    for (int i = 1; i <= n; ++i) {
        dis[i] = INF;
        vis[i] = false;
    }
    dis[start] = 0;
    for (int i = 1; i <= n; ++i) {
        int u = -1;
        for (int j = 1; j <= n; ++j)
            if (!vis[j] && (u == -1 || dis[j] < dis[u])) u = j;
        vis[u] = true;
        for (int e = head[u]; ~e; e = edge[e].next) {
            int v = edge[e].to;
            ll w = edge[e].dist;
            if (dis[v] > dis[u] + w)
                dis[v] = dis[u] + w;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) head[i] = -1;
    for (int i = 1; i <= n; ++i) {
        int a, b;
        ll w;
        scanf("%d%d%lld", &a, &b, &w);
        add(a, b, w);
        add(b, a, w);
    }
    double ans = 0;
    for (int i = 1; i <= n; ++i) {
        dijkstra(i);
        for (int j = 1; j <= n; ++j)
            ans = fmax(ans, (double)dis[j]);
    }
    printf("%.1lf\n", ans / 2);
    return 0;
}