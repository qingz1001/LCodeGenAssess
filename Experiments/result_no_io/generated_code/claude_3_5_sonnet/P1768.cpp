#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXN 7001
#define MAXM 20001
#define INF 1e9

typedef struct {
    int to, v, p, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], cnt;
int n, m;
double dis[MAXN];
bool vis[MAXN];
int que[MAXN], front, rear;

void add_edge(int from, int to, int v, int p) {
    edges[++cnt] = (Edge){to, v, p, head[from]};
    head[from] = cnt;
}

bool spfa(double mid) {
    for (int i = 1; i <= n; i++) {
        dis[i] = -INF;
        vis[i] = false;
    }
    front = rear = 0;

    for (int i = 1; i <= n; i++) {
        que[rear++] = i;
        vis[i] = true;
        dis[i] = 0;
    }

    while (front != rear) {
        int u = que[front++];
        if (front == MAXN) front = 0;
        vis[u] = false;

        for (int i = head[u]; i; i = edges[i].next) {
            int v = edges[i].to;
            double w = edges[i].v - mid * edges[i].p;
            if (dis[v] < dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    que[rear++] = v;
                    if (rear == MAXN) rear = 0;
                    vis[v] = true;
                    if (++edges[v].p > n) return true;
                }
            }
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, vi, pi;
        scanf("%d%d%d%d", &u, &v, &vi, &pi);
        add_edge(u, v, vi, pi);
    }

    double l = 0, r = 200;
    while (r - l > 1e-4) {
        double mid = (l + r) / 2;
        if (spfa(mid)) l = mid;
        else r = mid;
    }

    if (l < 1e-6) printf("-1\n");
    else printf("%.1f\n", l);

    return 0;
}