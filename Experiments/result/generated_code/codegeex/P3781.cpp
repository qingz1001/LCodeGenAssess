#include <stdio.h>
#include <string.h>
#define MOD 10007

int n, m, q;
int v[100005];
int head[100005], nxt[200005], to[200005], cnt;
int size[100005], f[100005][105];
int tmp[105];

void add(int x, int y) {
    nxt[++cnt] = head[x];
    to[cnt] = y;
    head[x] = cnt;
}

void dfs(int x, int fa) {
    size[x] = 1;
    f[x][v[x]] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y == fa) continue;
        dfs(y, x);
        for (int j = 0; j < m; j++) {
            tmp[j] = f[x][j];
            f[x][j] = 0;
        }
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                f[x][(j ^ k) % MOD] = (f[x][(j ^ k) % MOD] + f[x][j] * f[y][k]) % MOD;
            }
        }
        size[x] += size[y];
        for (int j = 0; j < m; j++) {
            f[x][j] = (f[x][j] + tmp[j]) % MOD;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        v[i] %= MOD;
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dfs(1, 0);
    scanf("%d", &q);
    while (q--) {
        char op[10];
        int x, y;
        scanf("%s%d", op, &x);
        if (op[0] == 'C') {
            scanf("%d", &y);
            y %= MOD;
            int d = (y - v[x] + MOD) % MOD;
            for (int i = head[x]; i; i = nxt[i]) {
                int y = to[i];
                for (int j = 0; j < m; j++) {
                    tmp[j] = f[x][j];
                    f[x][j] = 0;
                }
                for (int j = 0; j < m; j++) {
                    for (int k = 0; k < m; k++) {
                        f[x][(j ^ k) % MOD] = (f[x][(j ^ k) % MOD] + f[x][j] * f[y][k]) % MOD;
                    }
                }
                size[x] += size[y];
                for (int j = 0; j < m; j++) {
                    f[x][j] = (f[x][j] + tmp[j]) % MOD;
                }
            }
            v[x] = y;
        } else {
            printf("%d\n", f[1][x]);
        }
    }
    return 0;
}