#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAXN 100005
#define MAXM 200005
#define MOD 1000000007

int n, m, k, p;
int head[MAXN], to[MAXM], nxt[MAXM], weight[MAXM], cnt;
int dist[MAXN], f[MAXN];
bool vis[MAXN];

void add_edge(int u, int v, int w) {
    to[++cnt] = v;
    weight[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void spfa() {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    int q[MAXN], hh = 0, tt = -1;
    q[++tt] = 1;
    vis[1] = true;
    dist[1] = 0;
    
    while (hh <= tt) {
        int u = q[hh++];
        vis[u] = false;
        
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i], w = weight[i];
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!vis[v]) {
                    q[++tt] = v;
                    vis[v] = true;
                }
            }
        }
    }
}

int dfs(int u) {
    if (u == n) return 1;
    if (f[u] != -1) return f[u];
    
    f[u] = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = weight[i];
        if (dist[v] + w <= dist[n] + k) {
            f[u] = (f[u] + dfs(v)) % p;
        }
    }
    return f[u];
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &n, &m, &k, &p);
        
        memset(head, 0, sizeof(head));
        cnt = 0;
        
        for (int i = 1; i <= m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);
        }
        
        spfa();
        
        memset(f, -1, sizeof(f));
        int ans = dfs(1);
        
        if (ans == 0) printf("-1\n");
        else printf("%d\n", ans);
    }
    
    return 0;
}