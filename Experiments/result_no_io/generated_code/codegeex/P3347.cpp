#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define INF 0x3f3f3f3f

typedef long long ll;

struct Edge {
    int to, next;
    ll cap, flow, cost;
};

int n, m, head[210], tot = 1, s, t;
Edge edge[300010];
ll dis[210], pre[210], a[110], b[110], c[110], d[110], g[110][110];
bool vis[210];

void init() {
    memset(head, -1, sizeof(head));
    tot = 1;
}

void add_edge(int u, int v, ll cap, ll cost) {
    edge[tot] = {v, head[u], cap, 0, cost};
    head[u] = tot++;
    edge[tot] = {u, head[v], 0, 0, -cost};
    head[v] = tot++;
}

bool spfa() {
    for (int i = 0; i <= t; i++) {
        dis[i] = LLONG_MAX;
        vis[i] = false;
    }
    dis[s] = 0;
    vis[s] = true;
    pre[s] = 0;
    while (true) {
        int u = -1, minn = LLONG_MAX;
        for (int i = 0; i <= t; i++) {
            if (!vis[i] && dis[i] < minn) {
                minn = dis[i];
                u = i;
            }
        }
        if (u == -1) break;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            ll cap = edge[i].cap;
            ll cost = edge[i].cost;
            if (cap > 0 && dis[u] + cost < dis[v]) {
                dis[v] = dis[u] + cost;
                pre[v] = u;
                pre[t + 1] = i;
            }
        }
    }
    return vis[t];
}

ll min_cost_max_flow() {
    ll max_flow = 0, min_cost = 0;
    while (spfa()) {
        ll flow = LLONG_MAX;
        for (int i = t; i != s; i = pre[i]) {
            flow = flow < edge[pre[i]].cap ? flow : edge[pre[i]].cap;
        }
        for (int i = t; i != s; i = pre[i]) {
            edge[pre[i]].cap -= flow;
            edge[pre[i]^1].cap += flow;
            min_cost += flow * edge[pre[i]].cost;
        }
        max_flow += flow;
    }
    return max_flow;
}

int main() {
    scanf("%d%d", &n, &m);
    s = 0, t = n + m + 1;
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%lld", &d[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &g[i][j]);
        }
    }
    init();
    for (int i = 1; i <= n; i++) {
        add_edge(s, i, c[i], 0);
    }
    for (int i = 1; i <= m; i++) {
        add_edge(i + n, t, d[i], 0);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j]) {
                ll cost = a[i] * 2 * j + b[i];
                add_edge(i, j + n, INF, cost);
            }
        }
    }
    ll max_flow = min_cost_max_flow();
    printf("%lld\n", max_flow);
    return 0;
}