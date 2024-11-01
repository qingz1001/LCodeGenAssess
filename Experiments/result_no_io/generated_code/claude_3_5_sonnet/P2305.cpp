#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 200005
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

struct Edge {
    int to, next;
    ll len;
} edge[MAXN * 2];

int head[MAXN], cnt;
int n, t;
ll f[MAXN], s[MAXN], p[MAXN], q[MAXN], l[MAXN];
ll dis[MAXN], dp[MAXN];

void addEdge(int u, int v, ll w) {
    edge[++cnt].to = v;
    edge[cnt].len = w;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void dfs(int u, int fa) {
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        dis[v] = dis[u] + edge[i].len;
        dfs(v, u);
    }
}

void dp_tree(int u, int fa) {
    dp[u] = INF;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        dp_tree(v, u);
        if (dis[u] - dis[v] <= l[v]) {
            ll cost = (dis[u] - dis[v]) * p[v] + q[v];
            dp[u] = (dp[u] < cost) ? dp[u] : cost;
        }
        dp[u] = (dp[u] < dp[v]) ? dp[u] : dp[v];
    }
}

int main() {
    scanf("%d%d", &n, &t);
    for (int i = 2; i <= n; i++) {
        scanf("%lld%lld%lld%lld%lld", &f[i], &s[i], &p[i], &q[i], &l[i]);
        addEdge(f[i], i, s[i]);
        addEdge(i, f[i], s[i]);
    }

    dfs(1, 0);
    dp_tree(1, 0);

    for (int i = 2; i <= n; i++) {
        printf("%lld\n", dp[i]);
    }

    return 0;
}