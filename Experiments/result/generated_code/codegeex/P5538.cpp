#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 786433
#define N 200005

int n, a[N], deg[N], ans, s, f[N][32], sum[N][32];
int head[N], ver[N*2], nex[N*2], tot;

void add(int x, int y) {
    ver[tot] = y, nex[tot] = head[x], head[x] = tot++;
}

int lowbit(int x) {
    return x & -x;
}

void update(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
        ans = (ans + (long long)(v - sum[i][s]) * f[i][s] % MOD + MOD) % MOD;
        sum[i][s] = v;
    }
}

int query(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res = (res + sum[i][s]) % MOD;
    }
    return res;
}

void dfs(int x, int fa) {
    for (int i = head[x]; ~i; i = nex[i]) {
        int y = ver[i];
        if (y == fa) continue;
        dfs(y, x);
        for (int j = 0; j < 30; j++) {
            int v = (a[x] & (1 << j)) ? f[y][j] : 0;
            f[x][j] = (f[x][j] + v) % MOD;
        }
    }
    for (int j = 0; j < 30; j++) {
        f[x][j] = (f[x][j] + a[x] & (1 << j)) % MOD;
        update(f[x][j], f[x][j]);
    }
    ans = (ans + (long long)query(f[x][s]) * f[x][s] % MOD + MOD) % MOD;
    for (int j = 0; j < 30; j++) {
        update(f[x][j], 0);
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1, x, y; i < n; i++) {
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
        deg[x]++, deg[y]++;
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) s |= a[i];
    }
    dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}