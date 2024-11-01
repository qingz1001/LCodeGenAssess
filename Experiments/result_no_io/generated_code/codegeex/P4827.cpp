#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MOD 10007

int n, k;
int head[MAXN], next[MAXN << 1], ver[MAXN << 1], tot;
int size[MAXN], f[MAXN][151], son[MAXN], top[MAXN], d[MAXN], id[MAXN], idx;

void add(int x, int y) {
    ver[++tot] = y;
    next[tot] = head[x];
    head[x] = tot;
}

void dfs1(int x, int fa) {
    d[x] = d[fa] + 1;
    size[x] = 1;
    int maxson = -1;
    for (int i = head[x]; i; i = next[i]) {
        int y = ver[i];
        if (y == fa) continue;
        dfs1(y, x);
        size[x] += size[y];
        if (size[y] > maxson) maxson = size[y], son[x] = y;
    }
}

void dfs2(int x, int topf) {
    top[x] = topf;
    id[x] = ++idx;
    if (!son[x]) return;
    dfs2(son[x], topf);
    for (int i = head[x]; i; i = next[i]) {
        int y = ver[i];
        if (y == son[x] || y == topf) continue;
        dfs2(y, y);
    }
}

int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (d[top[x]] < d[top[y]]) y = ver[head[top[y]]];
        else x = ver[head[top[x]]];
    }
    if (d[x] > d[y]) return y;
    return x;
}

int dis(int x, int y) {
    return d[x] + d[y] - 2 * d[lca(x, y)];
}

int quick_pow(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) res = (long long)res * x % MOD;
        x = (long long)x * x % MOD;
        y >>= 1;
    }
    return res;
}

void init() {
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++) f[i][0] = 1;
    for (int j = 1; j <= k; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = (f[i][j - 1] + (long long)f[son[i]][j - 1] * (size[i] - size[son[i]]) % MOD) % MOD;
        }
    }
}

int solve(int x, int d) {
    if (d < 0) return 0;
    int res = 0;
    for (int i = x; i; i = ver[head[top[i]]]) {
        res = (res + (long long)f[i][d] * size[i] % MOD) % MOD;
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    init();
    for (int i = 1; i <= n; i++) {
        int ans = 0;
        for (int j = 1; j <= n; j++) {
            ans = (ans + (long long)quick_pow(dis(i, j), k) * solve(j, k - 1)) % MOD;
        }
        printf("%d\n", ans);
    }
    return 0;
}