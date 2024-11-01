#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 100005
#define MAX_M 200005
#define INF 0x3f3f3f3f

typedef long long ll;

struct Edge {
    int to, next, weight;
} edges[MAX_M];

int head[MAX_N], dist[MAX_N], cnt;
ll dp[MAX_N];
bool vis[MAX_N];

void add_edge(int u, int v, int w) {
    edges[++cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt;
}

void dijkstra(int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        vis[i] = false;
    }
    dist[1] = 0;
    
    for (int i = 1; i <= n; i++) {
        int u = 0, min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == 0) break;
        vis[u] = true;
        
        for (int e = head[u]; e; e = edges[e].next) {
            int v = edges[e].to, w = edges[e].weight;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

ll dfs(int u, int n, int k, int p) {
    if (dp[u] != -1) return dp[u];
    if (u == n) return 1;
    
    ll res = 0;
    for (int e = head[u]; e; e = edges[e].next) {
        int v = edges[e].to, w = edges[e].weight;
        if (dist[u] + w <= dist[n] + k) {
            res = (res + dfs(v, n, k, p)) % p;
        }
    }
    return dp[u] = res;
}

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n, m, k, p;
        scanf("%d %d %d %d", &n, &m, &k, &p);
        
        cnt = 0;
        memset(head, 0, sizeof(head));
        memset(dp, -1, sizeof(dp));
        
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            add_edge(u, v, w);
        }
        
        dijkstra(n);
        
        ll ans = dfs(1, n, k, p);
        printf("%lld\n", ans == 0 ? -1 : ans);
    }
    
    return 0;
}