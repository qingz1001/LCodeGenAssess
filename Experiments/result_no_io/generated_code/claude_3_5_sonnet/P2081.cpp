#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

typedef long long ll;

struct Edge {
    int to, next;
    ll w;
} e[MAXM];

int head[MAXN], cnt;
int n, m;
ll dp[MAXN], sz[MAXN];
double ans;

void add_edge(int u, int v, ll w) {
    e[++cnt] = (struct Edge){v, head[u], w};
    head[u] = cnt;
}

void dfs(int u, int fa) {
    sz[u] = 1;
    dp[u] = 0;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u);
        dp[u] += dp[v] + e[i].w * sz[v];
        sz[u] += sz[v];
    }
}

void dfs2(int u, int fa, ll up) {
    ans += (double)(dp[u] + up) / n;
    ll sum = dp[u] + up;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        ll new_up = sum - dp[v] - e[i].w * sz[v] + e[i].w * (n - sz[v]);
        dfs2(v, u, new_up);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    
    dfs(1, 0);
    dfs2(1, 0, 0);
    
    printf("%.5f\n", ans);
    
    return 0;
}