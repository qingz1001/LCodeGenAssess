#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define MAXM 5005
#define INF 1e9

int n, m;
int F[MAXN];
int head[MAXN], to[MAXM], nxt[MAXM], weight[MAXM], cnt;
double dist[MAXN];
int vis[MAXN];

void add_edge(int u, int v, int w) {
    to[++cnt] = v;
    weight[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

int spfa(double mid) {
    for (int i = 1; i <= n; i++) {
        dist[i] = -INF;
        vis[i] = 0;
    }
    dist[1] = 0;
    vis[1] = 1;
    
    int q[MAXN], front = 0, rear = 0;
    q[rear++] = 1;
    
    while (front != rear) {
        int u = q[front++];
        if (front == MAXN) front = 0;
        vis[u] = 0;
        
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            double w = F[v] - mid * weight[i];
            if (dist[v] < dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!vis[v]) {
                    vis[v] = 1;
                    q[rear++] = v;
                    if (rear == MAXN) rear = 0;
                    if (++vis[v] > n) return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &F[i]);
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
    }
    
    double l = 0, r = 1000, ans = 0;
    while (r - l > 1e-4) {
        double mid = (l + r) / 2;
        if (spfa(mid)) {
            l = mid;
            ans = mid;
        } else {
            r = mid;
        }
    }
    
    printf("%.2f\n", ans);
    return 0;
}