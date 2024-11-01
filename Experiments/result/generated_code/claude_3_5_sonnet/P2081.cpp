#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

typedef struct Edge {
    int to, next, weight;
} Edge;

Edge edges[MAXM];
int head[MAXN], cnt;
int n, m;
double dp[MAXN], sum[MAXN];
int vis[MAXN], deg[MAXN];

void addEdge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
    deg[u]++;
}

void dfs(int u, int fa) {
    vis[u] = 1;
    double total = 0;
    int child = 0;
    
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == fa) continue;
        if (!vis[v]) {
            dfs(v, u);
            total += sum[v] + edges[i].weight * (double)deg[v] / (deg[v] - 1);
            child++;
        }
    }
    
    if (child == 0) {
        dp[u] = sum[u] = 0;
        return;
    }
    
    dp[u] = total / child;
    sum[u] = total * deg[u] / (deg[u] - 1);
}

int findRoot() {
    for (int i = 1; i <= n; i++) {
        if (deg[i] > 1) return i;
    }
    return 1;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    
    int root = findRoot();
    dfs(root, 0);
    
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += dp[i];
    }
    
    printf("%.5f\n", ans / n);
    
    return 0;
}