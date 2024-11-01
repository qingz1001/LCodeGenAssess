#include <stdio.h>
#include <stdlib.h>

#define MAXN 205
#define MAXM 40005

int n, m, a[MAXN][MAXN], cnt, head[MAXM], to[MAXM << 1], nxt[MAXM << 1], dep[MAXM], S, T, cur[MAXM], q[MAXM], v[MAXM];

void add(int x, int y, int z) {
    cnt++;
    to[cnt] = y;
    nxt[cnt] = head[x];
    head[x] = cnt;
    dep[cnt] = z;
}

void bfs() {
    int i, u, v, x, y;
    for (i = 1; i <= T; i++) cur[i] = head[i], dep[i] = 0;
    q[1] = S;
    dep[S] = 1;
    v[S] = 1;
    for (i = 1; i <= T; i++) {
        u = q[i];
        for (v = head[u]; v; v = nxt[v]) {
            x = to[v];
            y = dep[v];
            if (!dep[x] && y) {
                dep[x] = y + 1;
                q[++cnt] = x;
                v = cur[x];
                v = head[x];
                v = nxt[v];
            }
        }
    }
}

int dfs(int u, int f) {
    int i, x, y, t = 0;
    if (u == T) return f;
    for (i = cur[u]; i && t < f; i = nxt[i]) {
        cur[u] = i;
        x = to[i];
        y = dep[v];
        if (dep[x] == dep[u] + 1 && y) {
            y = dfs(x, f - t);
            dep[v] -= y;
            dep[x] += y;
            t += y;
        }
    }
    if (!t) dep[u] = 0;
    return t;
}

int main() {
    int i, j, k, x, y, ans = 0;
    scanf("%d%d", &n, &m);
    S = 0;
    T = n * m * 2 + 1;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] == 0) {
                add(S, (i - 1) * m + j, 1);
                add((i - 1) * m + j, S, 0);
                add((i - 1) * m + j + n * m, T, 1);
                add(T, (i - 1) * m + j + n * m, 0);
                if (a[i - 1][j] == 0) {
                    add((i - 1) * m + j, (i - 2) * m + j + n * m, 1);
                    add((i - 2) * m + j + n * m, (i - 1) * m + j, 0);
                }
                if (a[i][j - 1] == 0) {
                    add((i - 1) * m + j, i * m + j - 1 + n * m, 1);
                    add(i * m + j - 1 + n * m, (i - 1) * m + j, 0);
                }
            }
        }
    }
    while (1) {
        bfs();
        if (!dep[T]) break;
        ans += dfs(S, 1000000000);
    }
    printf("%d\n", ans);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (a[i][j] == 0 && dep[(i - 1) * m + j] == 1) {
                printf("%d %d\n", i, j);
            }
        }
    }
    return 0;
}