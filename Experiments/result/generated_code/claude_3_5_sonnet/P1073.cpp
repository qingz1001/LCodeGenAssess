#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX_M 500005
#define INF 0x3f3f3f3f

struct Edge {
    int to, next;
} edge[MAX_M], edge_rev[MAX_M];

int head[MAX_N], head_rev[MAX_N], ecnt, ecnt_rev;
int n, m, price[MAX_N];
int min_price[MAX_N], max_price[MAX_N];
int queue[MAX_N], vis[MAX_N];

void add_edge(int u, int v, int rev) {
    edge[ecnt].to = v;
    edge[ecnt].next = head[u];
    head[u] = ecnt++;
    
    if (rev) {
        edge_rev[ecnt_rev].to = u;
        edge_rev[ecnt_rev].next = head_rev[v];
        head_rev[v] = ecnt_rev++;
    }
}

void spfa(int s, int *dist, struct Edge *e, int *h) {
    int front = 0, rear = 0;
    memset(vis, 0, sizeof(vis));
    
    queue[rear++] = s;
    vis[s] = 1;
    
    while (front < rear) {
        int u = queue[front++];
        vis[u] = 0;
        
        for (int i = h[u]; ~i; i = e[i].next) {
            int v = e[i].to;
            if (dist[v] > dist[u]) {
                dist[v] = dist[u];
                if (!vis[v]) {
                    queue[rear++] = v;
                    vis[v] = 1;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    
    memset(head, -1, sizeof(head));
    memset(head_rev, -1, sizeof(head_rev));
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int u, v, z;
        scanf("%d%d%d", &u, &v, &z);
        add_edge(u, v, 0);
        if (z == 2) add_edge(v, u, 0);
        add_edge(v, u, 1);
    }
    
    for (int i = 1; i <= n; i++) {
        min_price[i] = INF;
        max_price[i] = -INF;
    }
    
    min_price[1] = price[1];
    max_price[n] = price[n];
    
    spfa(1, min_price, edge, head);
    spfa(n, max_price, edge_rev, head_rev);
    
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (min_price[i] != INF && max_price[i] != -INF) {
            int profit = max_price[i] - min_price[i];
            if (profit > ans) ans = profit;
        }
    }
    
    printf("%d\n", ans);
    
    return 0;
}