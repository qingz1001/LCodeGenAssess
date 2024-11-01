#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005

int n;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], tot;
int size[MAXN], dep[MAXN], f[MAXN];

void add(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs1(int u, int fa) {
    size[u] = 1;
    dep[u] = dep[fa] + 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs1(v, u);
        size[u] += size[v];
    }
}

void dfs2(int u, int fa) {
    f[u] = f[fa] + n - 2 * size[u];
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs2(v, u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }

    dfs1(1, 0);
    f[1] = dep[1] = 0;
    for (int i = head[1]; i; i = nxt[i]) {
        int v = to[i];
        f[1] += dep[v];
    }
    dfs2(1, 0);

    int ans = 1;
    for (int i = 2; i <= n; i++) {
        if (f[i] < f[ans]) {
            ans = i;
        }
    }

    printf("%d %d\n", ans, f[ans]);

    return 0;
}