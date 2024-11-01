#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 505
#define MAXM 2000005
#define INF LLONG_MAX

typedef long long ll;

struct Edge {
    int v, nxt, c;
    ll w;
} edge[MAXM];

int head[MAXN * MAXN], cnt;
int n;
ll dis[MAXN * MAXN], a[MAXN][MAXN];
int vis[MAXN * MAXN];
int sx, sy, tx, ty;

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
}

void add(int u, int v, int c, ll w) {
    edge[cnt].v = v;
    edge[cnt].nxt = head[u];
    edge[cnt].c = c;
    edge[cnt].w = w;
    head[u] = cnt++;
}

void add_edge(int u, int v, int c, ll w) {
    add(u, v, c, w);
    add(v, u, 0, -w);
}

void spfa() {
    int que[MAXN * MAXN];
    int front = 0, rear = 0;
    for (int i = 0; i <= n * n; i++) {
        dis[i] = INF;
        vis[i] = 0;
    }
    dis[sx] = 0;
    que[rear++] = sx;
    while (front < rear) {
        int u = que[front++];
        vis[u] = 0;
        for (int i = head[u]; i != -1; i = edge[i].nxt) {
            int v = edge[i].v;
            ll w = edge[i].w;
            if (edge[i].c > 0 && dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    que[rear++] = v;
                    vis[v] = 1;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    n++;
    init();
    sx = 1;
    sy = 1;
    tx = n;
    ty = n;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            add_edge(i * n + j, i * n + j + 1, a[i][j], 0);
            add_edge(i * n + j, i * n + j + 1, INF, 1);
            add_edge((i + 1) * n + j, (i + 1) * n + j - 1, a[i + 1][j], 0);
            add_edge((i + 1) * n + j, (i + 1) * n + j - 1, INF, 1);
            add_edge(i * n + j, (i + 1) * n + j, INF, 0);
            add_edge(i * n + j, (i + 1) * n + j, INF, -1);
            add_edge(i * n + j + 1, (i + 1) * n + j - 1, INF, 0);
            add_edge(i * n + j + 1, (i + 1) * n + j - 1, INF, -1);
        }
    }
    add_edge(sx + (sy - 1) * n, tx + (ty - 1) * n, INF, 0);
    spfa();
    printf("%lld\n", dis[tx + (ty - 1) * n]);
    return 0;
}