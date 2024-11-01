#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 50010
#define MAXM 50010
#define MAXP 500010
#define MAXLOG 20

int n, m;
int head[MAXN], ver[MAXM * 2], nex[MAXM * 2], tot;
int fa[MAXN][MAXLOG], dep[MAXN];
int dfn[MAXN], low[MAXN], c[MAXN], cnt, sz[MAXN];
int stk[MAXN], top;
char s[MAXN], t[MAXM];
int ans;

void add(int x, int y) {
    ver[tot] = y;
    nex[tot] = head[x];
    head[x] = tot++;
}

void dfs(int x, int f) {
    dfn[x] = low[x] = ++cnt;
    for (int i = 1; i <= MAXLOG; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = head[x]; ~i; i = nex[i]) {
        int y = ver[i];
        if (y == f) continue;
        dep[y] = dep[x] + 1;
        fa[y][0] = x;
        dfs(y, x);
        low[x] = low[y];
    }
    if (low[x] == dfn[x]) {
        c[x] = ++cnt;
        sz[cnt] = 1;
        stk[++top] = x;
        while (stk[top] != x) {
            c[stk[top]] = cnt;
            sz[cnt]++;
            top--;
        }
        top--;
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) {
        int t = x;
        x = y;
        y = t;
    }
    for (int i = MAXLOG - 1; i >= 0; i--) {
        if (dep[fa[x][i]] >= dep[y]) {
            x = fa[x][i];
        }
    }
    if (x == y) return x;
    for (int i = MAXLOG - 1; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i] == t[j]) {
                int k = j + sz[c[i]] - 1;
                if (k <= m) {
                    ans++;
                }
            }
        }
    }
    printf("%d\n", ans * 2);
    return 0;
}