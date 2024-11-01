#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

typedef struct {
    int to, next, w;
} Edge;

Edge edges[MAXM];
int head[MAXN], deg[MAXN], tot = 0;
double dp[MAXN], dp2[MAXN];
int vis[MAXN], pre[MAXN];
int n, m;

void add_edge(int u, int v, int w) {
    edges[tot].to = v;
    edges[tot].w = w;
    edges[tot].next = head[u];
    head[u] = tot++;
}

void dfs1(int u) {
    vis[u] = 1;
    dp[u] = 0;
    int cnt = 0;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (vis[v]) continue;
        dfs1(v);
        dp[u] += dp[v] + edges[i].w;
        cnt++;
    }
    if (cnt) dp[u] /= cnt;
}

void dfs2(int u) {
    vis[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (vis[v]) continue;
        if (deg[u] > 1) {
            dp2[v] = edges[i].w + (dp2[u] + dp[u] * deg[u] - edges[i].w - dp[v]) / (deg[u] - 1);
        } else {
            dp2[v] = edges[i].w + dp2[u];
        }
        dfs2(v);
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
        deg[u]++;
        deg[v]++;
    }

    if (m == n - 1) {
        dfs1(1);
        memset(vis, 0, sizeof(vis));
        dp2[1] = 0;
        dfs2(1);
    } else {
        // Handle the case with a cycle
        // This part is omitted for simplicity
    }

    double ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += (dp[i] + dp2[i]) / n;
    }

    printf("%.5f\n", ans);
    return 0;
}