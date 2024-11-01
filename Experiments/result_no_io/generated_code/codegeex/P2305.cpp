#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAXN 200005
#define MAXM 200005
#define MAXLOG 20
#define INF LLONG_MAX

typedef long long ll;

struct Edge {
    int to;
    ll weight;
} edges[MAXN * 2];

int head[MAXN], degree[MAXN], parent[MAXN], depth[MAXN];
ll distance[MAXN], price_p[MAXN], price_q[MAXN], limit[MAXN];
ll dp[MAXN][MAXLOG];
int st[MAXN][MAXLOG];

void add_edge(int u, int v, ll w) {
    static int tot = 0;
    edges[tot].to = v;
    edges[tot].weight = w;
    head[u] = tot++;
}

void dfs(int u) {
    for (int i = 1; i < MAXLOG; i++) {
        st[u][i] = st[st[u][i-1]][i-1];
        dp[u][i] = dp[st[u][i-1]][i-1] + dp[u][i-1];
    }
    for (int i = head[u]; i != -1; i = edges[i].to) {
        int v = edges[i].to;
        depth[v] = depth[u] + 1;
        parent[v] = u;
        distance[v] = distance[u] + edges[i].weight;
        dp[v][0] = price_p[v] * distance[v] + price_q[v];
        st[v][0] = u;
        dfs(v);
    }
}

ll query(int u, int v) {
    ll ans = 0;
    for (int i = MAXLOG - 1; i >= 0; i--) {
        if (depth[st[u][i]] >= depth[v]) {
            ans += dp[u][i];
            u = st[u][i];
        }
    }
    return ans;
}

ll get_min_cost(int u, ll d) {
    if (distance[u] <= d) {
        return query(u, parent[u]);
    }
    int l = 0, r = depth[u] - depth[parent[u]] - 1;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (distance[u] - distance[st[u][mid]] <= d) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return query(st[u][l], parent[u]) + price_p[u] * (d + distance[parent[u]] - distance[st[u][l]]) + price_q[u];
}

int main() {
    int n, t;
    scanf("%d %d", &n, &t);
    memset(head, -1, sizeof(head));
    for (int i = 2; i <= n; i++) {
        int f;
        ll s, p, q, l;
        scanf("%d %lld %lld %lld %lld", &f, &s, &p, &q, &l);
        add_edge(f, i, s);
        degree[f]++;
        parent[i] = f;
        distance[i] = s;
        price_p[i] = p;
        price_q[i] = q;
        limit[i] = l;
    }
    depth[1] = 0;
    dfs(1);
    for (int i = 2; i <= n; i++) {
        printf("%lld\n", get_min_cost(i, limit[i]));
    }
    return 0;
}