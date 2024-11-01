#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 150005
#define MAX_M 300005
#define INF 0x3f3f3f3f

typedef long long ll;

int n, m, s, t, k;
int head[MAX_N], ver[MAX_M], edge[MAX_M], next[MAX_M], tot;
int d[MAX_N], cur[MAX_N], h[MAX_N];
int q[MAX_N], qt, qh;
ll ans[MAX_M];
bool vis[MAX_N];

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, next[tot] = head[x], head[x] = tot;
    ver[++tot] = x, edge[tot] = 0, next[tot] = head[y], head[y] = tot;
}

bool bfs() {
    memset(d, 0, sizeof(d));
    qt = qh = 0;
    q[qt++] = s;
    d[s] = 1;
    while (qt > qh) {
        int x = q[qh++];
        for (int i = head[x]; i; i = next[i]) {
            int y = ver[i];
            if (edge[i] && !d[y]) {
                d[y] = d[x] + 1;
                q[qt++] = y;
                if (y == t) return true;
            }
        }
    }
    return false;
}

int dfs(int x, int flow) {
    if (x == t) return flow;
    int rest = flow;
    for (int &i = cur[x]; i; i = next[i]) {
        int y = ver[i];
        if (edge[i] && d[y] == d[x] + 1) {
            int k = dfs(y, rest < edge[i] ? rest : edge[i]);
            if (!k) d[y] = 0;
            edge[i] -= k;
            edge[i ^ 1] += k;
            rest -= k;
            if (!rest) break;
        }
    }
    return flow - rest;
}

ll dinic() {
    ll maxflow = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        maxflow += dfs(s, INF);
    }
    return maxflow;
}

void dfs2(int x) {
    vis[x] = true;
    for (int i = head[x]; i; i = next[i]) {
        int y = ver[i];
        if (edge[i] && !vis[y]) dfs2(y);
    }
}

int cmp(const void *a, const void *b) {
    return *(ll*)a > *(ll*)b ? 1 : -1;
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);
    tot = 1;
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
    }

    ll flow = dinic();
    dfs2(s);

    int cnt = 0;
    for (int i = 2; i <= tot; i += 2) {
        if (vis[ver[i ^ 1]] && !vis[ver[i]]) {
            ans[++cnt] = edge[i ^ 1];
        }
    }

    qsort(ans + 1, cnt, sizeof(ll), cmp);

    ll sum = 0;
    for (int i = 1; i <= k && i <= cnt; i++) {
        sum += ans[i];
        printf("%lld\n", sum);
    }

    if (k > cnt) printf("-1\n");

    return 0;
}