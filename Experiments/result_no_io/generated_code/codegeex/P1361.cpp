#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f

typedef struct {
    int from;
    int to;
    int cap;
    int cost;
    int next;
} Edge;

int n, m, s, t, head[2005], tot = 1;
Edge e[2000005];
int dis[2005], pre[2005], incf[2005], vis[2005], cur[2005];

void addEdge(int u, int v, int cap, int cost) {
    e[++tot].to = v;
    e[tot].cap = cap;
    e[tot].cost = cost;
    e[tot].next = head[u];
    head[u] = tot;

    e[++tot].to = u;
    e[tot].cap = 0;
    e[tot].cost = -cost;
    e[tot].next = head[v];
    head[v] = tot;
}

int spfa() {
    for (int i = 0; i <= t; i++) {
        dis[i] = INF;
        pre[i] = -1;
        incf[i] = 0;
        vis[i] = 0;
        cur[i] = head[i];
    }

    dis[s] = 0;
    incf[s] = INF;
    vis[s] = 1;

    int u, v;
    while (1) {
        u = -1;
        for (int i = 0; i <= t; i++) {
            if (!vis[i] && dis[i] < dis[u]) u = i;
        }
        if (u == -1) break;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].next) {
            v = e[i].to;
            if (e[i].cap && dis[u] + e[i].cost < dis[v]) {
                dis[v] = dis[u] + e[i].cost;
                pre[v] = u;
                incf[v] = (incf[u] < e[i].cap ? incf[u] : e[i].cap);
                cur[v] = head[v];
            }
        }
    }
    return incf[t];
}

int minCostMaxFlow() {
    int res = 0;
    while (spfa()) {
        int u = t;
        while (u != s) {
            e[cur[pre[u]]].cap -= incf[t];
            e[cur[pre[u]]^1].cap += incf[t];
            u = pre[u];
        }
        res += incf[t] * dis[t];
    }
    return res;
}

int main() {
    scanf("%d", &n);
    s = 0;
    t = 2 * n + 1;
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(s, i, 1, -a);
        addEdge(i, n + i, 1, 0);
        addEdge(n + i, t, 1, -b);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int k, c1, c2;
        scanf("%d%d%d", &k, &c1, &c2);
        addEdge(s, t + i, 1, -c1);
        addEdge(t + i, t + m + i, 1, -c2);
        for (int j = 1; j <= k; j++) {
            int x;
            scanf("%d", &x);
            addEdge(t + i, x, 1, 0);
            addEdge(x, t + m + i, 1, 0);
        }
    }
    printf("%d\n", -minCostMaxFlow());
    return 0;
}