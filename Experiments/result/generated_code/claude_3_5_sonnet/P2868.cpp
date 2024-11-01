#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 1005
#define MAX_M 5005
#define INF 1e9

int n, m;
int F[MAX_N];
int head[MAX_N], to[MAX_M], nxt[MAX_M], weight[MAX_M], cnt;
double dist[MAX_N];
int vis[MAX_N];

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
    
    int queue[MAX_N], front = 0, rear = 0;
    queue[rear++] = 1;
    
    while (front != rear) {
        int u = queue[front++];
        if (front == MAX_N) front = 0;
        vis[u] = 0;
        
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            double new_dist = dist[u] + F[v] - mid * weight[i];
            if (new_dist > dist[v]) {
                dist[v] = new_dist;
                if (!vis[v]) {
                    vis[v] = 1;
                    queue[rear++] = v;
                    if (rear == MAX_N) rear = 0;
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
    
    double l = 0, r = 1000;
    while (r - l > 1e-4) {
        double mid = (l + r) / 2;
        if (spfa(mid)) l = mid;
        else r = mid;
    }
    
    printf("%.2f\n", l);
    return 0;
}