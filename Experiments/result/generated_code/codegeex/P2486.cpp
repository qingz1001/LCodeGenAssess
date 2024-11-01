#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 200005

int n, m;
int w[MAXN];
int head[MAXN], to[MAXM], nxt[MAXM], tot;
int fa[MAXN][20], dep[MAXN];

void add(int x, int y) {
    to[tot] = y;
    nxt[tot] = head[x];
    head[x] = tot++;
}

void dfs(int x, int f) {
    fa[x][0] = f;
    for (int i = 1; i < 20; i++) {
        fa[x][i] = fa[fa[x][i-1]][i-1];
    }
    for (int i = head[x]; i != -1; i = nxt[i]) {
        int y = to[i];
        if (y != f) {
            dep[y] = dep[x] + 1;
            dfs(y, x);
        }
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) {
        int tmp = x;
        x = y;
        y = tmp;
    }
    for (int i = 19; i >= 0; i--) {
        if (dep[fa[x][i]] >= dep[y]) {
            x = fa[x][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = 19; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dep[1] = 1;
    dfs(1, 0);
    while (m--) {
        char op[2];
        int x, y, c;
        scanf("%s%d%d", op, &x, &y);
        if (op[0] == 'C') {
            scanf("%d", &c);
            int z = lca(x, y);
            // 染色操作的具体实现
        } else if (op[0] == 'Q') {
            // 查询操作的具体实现
        }
    }
    return 0;
}