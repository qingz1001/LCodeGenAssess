#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300005
#define MAXM 600005
#define INF 0x3f3f3f3f

struct Edge {
    int to, next, w;
} edge[MAXM];

int head[MAXN], cnt;
int n, s;
int f[MAXN], g[MAXN], size[MAXN];
int maxd[MAXN], sec[MAXN], node[MAXN];

void addEdge(int u, int v, int w) {
    edge[++cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void dfs1(int u, int fa) {
    size[u] = 1;
    f[u] = 0;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs1(v, u);
        size[u] += size[v];
        int tmp = f[v] + edge[i].w;
        if (tmp > f[u]) f[u] = tmp;
    }
}

void dfs2(int u, int fa) {
    maxd[u] = sec[u] = -INF;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        int tmp = f[v] + edge[i].w;
        if (tmp >= maxd[u]) {
            sec[u] = maxd[u];
            maxd[u] = tmp;
            node[u] = v;
        } else if (tmp > sec[u]) {
            sec[u] = tmp;
        }
    }
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        if (node[u] == v) g[v] = (g[u] > sec[u] ? g[u] : sec[u]) + edge[i].w;
        else g[v] = (g[u] > maxd[u] ? g[u] : maxd[u]) + edge[i].w;
        dfs2(v, u);
    }
}

int check(int mid) {
    int res = INF, sum = 0;
    for (int i = 1; i <= n; i++) {
        if (f[i] <= mid && g[i] <= mid) {
            int tmp = (mid - f[i]) + (mid - g[i]);
            if (tmp < res) {
                res = tmp;
                sum = f[i] > g[i] ? f[i] : g[i];
            }
        }
    }
    return sum <= s ? res : -1;
}

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    
    dfs1(1, 0);
    dfs2(1, 0);
    
    int l = 0, r = INF, ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int tmp = check(mid);
        if (tmp != -1) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    
    printf("%d\n", ans);
    return 0;
}