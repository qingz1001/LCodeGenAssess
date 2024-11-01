#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005

int n;
int head[MAXN], nxt[MAXN*2], to[MAXN*2], tot;

void add(int u, int v) {
    to[tot] = v;
    nxt[tot] = head[u];
    head[u] = tot++;
}

int sz[MAXN], maxsz[MAXN], rt, all;
int vis[MAXN];

void dfs1(int x, int fa) {
    sz[x] = 1;
    maxsz[x] = 0;
    for (int i = head[x]; ~i; i = nxt[i]) {
        if (to[i] != fa && !vis[to[i]]) {
            dfs1(to[i], x);
            sz[x] += sz[to[i]];
            maxsz[x] = (maxsz[x] < sz[to[i]]) ? sz[to[i]] : maxsz[x];
        }
    }
    maxsz[x] = (maxsz[x] < all - sz[x]) ? all - sz[x] : maxsz[x];
    if (maxsz[x] < maxsz[rt]) rt = x;
}

double ans = 0.0;

void dfs2(int x, int fa, int s) {
    ans += s;
    for (int i = head[x]; ~i; i = nxt[i]) {
        if (to[i] != fa && !vis[to[i]]) {
            dfs2(to[i], x, s + all - sz[to[i]]);
        }
    }
}

void solve(int x) {
    vis[x] = 1;
    dfs2(x, -1, all - sz[x]);
    for (int i = head[x]; ~i; i = nxt[i]) {
        if (!vis[to[i]]) {
            rt = 0;
            all = sz[to[i]];
            dfs1(to[i], x);
            solve(rt);
        }
    }
}

int main() {
    scanf("%d", &n);
    all = n;
    for (int i = 0; i < n; i++) head[i] = -1;
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    rt = 0;
    dfs1(0, -1);
    solve(rt);
    printf("%.4lf\n", ans / n);
    return 0;
}